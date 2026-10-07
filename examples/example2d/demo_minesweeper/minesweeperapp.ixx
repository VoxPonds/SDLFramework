module;

export module example2d.minesweeperapp;
import engine.core.appconfig;
import engine.core.timer;
import engine.core.random;
import engine.core.eventtype;
import engine.core.appcontext;
import engine.core.math;
import engine.platform.inputsystem;
import engine.platform.inputcode;
import engine.resource.resourcemanager;
import engine.render.framerecorder;
import engine.render.apprenderer;
import engine.render.framedata;
import std;

export
{
    enum class MinesweeperAction : std::uint8_t
    {
        ACTION_OPEN_CELL,
        ACTION_FLAG_CELL,
    };

    enum class GridState : std::uint8_t
    {
        CLOSED,
        OPENED,
        FLAGGED,
    };

    struct GridPos
    {
        std::size_t row {};
        std::size_t column {};

        friend bool operator==(const GridPos&, const GridPos&) = default;
    };

    struct GridInfo
    {
        GridPos position {};
        bool is_mine {false};
        std::uint16_t adjacent_mine {};
        GridState state {GridState::CLOSED};
    };

    struct MineField
    {
        std::vector<GridInfo> board;
    };

    inline constexpr math::BaseColor color_black{
        .r {0.0f},
        .g {0.0f},
        .b {0.0f},
        .a {1.0f}
    };

    inline constexpr math::BaseColor color_white{
        .r {1.0f},
        .g {1.0f},
        .b {1.0f},
        .a {1.0f}
    };

    inline constexpr math::BaseColor color_grey{
        .r {0.3f},
        .g {0.3f},
        .b {0.3f},
        .a {1.0f}
    };

    struct MinesweeperApp
    {
        using MinesweeperInputSystem = engine::platform::DefaultInputSystem;

        private:
            inline static constinit math::Vector2 board_origin_ {};
            inline static constinit std::size_t board_width_ {15};
            inline static constinit std::size_t board_height_ {15};
            inline static constinit std::size_t cell_size_ {30};
            inline static constinit std::size_t mine_count_ {30};
            inline static float move_interval {0.15f};
            inline static float move_timer_ {0.0f};

            bool mines_generated_;
            bool game_over_;
            engine::core::Random random_;

            engine::render::AppRenderer app_renderer_;
            MinesweeperInputSystem& input_system_;

            std::vector<GridInfo> mine_field_;
            std::mdspan<GridInfo, std::dextents<std::size_t, 2>> mine_field_view_;

        public:
            static constexpr auto config() -> engine::core::AppConfig;

            explicit MinesweeperApp(const engine::core::AppContext& context);

            void init();

            void update(Timer::DeltaTimeType deltaTime);

            void draw();

        private:
            void forEachNeighbor(std::size_t row, std::size_t column, auto&& predicate);

            void handleInput();

            void openCell(GridPos position);

            void initialOpenCell(std::size_t row, std::size_t column);

            void expandZeroArea(std::size_t row, std::size_t column);

            void toggleFlag(GridPos position);

            void generateMines();

            void updateBoard();

            static auto screenToBoard(math::Vector2 position) -> GridPos;

            bool gridInTheBoard(GridPos position) const;

            void createBoard(std::size_t width, std::size_t height);

            void drawBoard() const;

            bool checkWin() const;
    };
}

void MinesweeperApp::forEachNeighbor(const std::size_t row, const std::size_t column, auto&& predicate)
{
    const auto row_begin = row > 0 ? row - 1 : 0uz;
    const auto row_end = std::min(row + 2, mine_field_view_.extent(0));

    const auto column_begin = column > 0 ? column - 1 : 0uz;
    const auto column_end = std::min(column + 2, mine_field_view_.extent(1));

    const auto neighbor_view = std::views::cartesian_product(
             std::views::iota(row_begin, row_end),
             std::views::iota(column_begin, column_end)
    );
    for (const auto [neighbor_row, neighbor_column] : neighbor_view)
    {
        if (neighbor_row == row && neighbor_column == column)
        {
            continue;
        }
        std::invoke_r<void>(std::forward<decltype(predicate)>(predicate),mine_field_view_[neighbor_row, neighbor_column]);
    }
}

constexpr auto MinesweeperApp::config() -> engine::core::AppConfig
{
    return engine::core::AppConfig{
        .window_config_{
            .width {board_width_ * cell_size_},
            .height {board_height_ * cell_size_},
            .title {"Demo Minesweeper"},
            .flags {16},
        },

    };
}

MinesweeperApp::MinesweeperApp(const engine::core::AppContext& context) :
    mines_generated_(false),
    game_over_(false),
    random_(),
    app_renderer_(context.recorder),
    input_system_(context.input_system),
    mine_field_(board_width_ * board_height_),
    mine_field_view_(mine_field_.data(), board_height_, board_width_)
{
}

void MinesweeperApp::init()
{
    for (const auto [row, column] :
        std::views::cartesian_product(
            std::views::iota(0uz, board_height_),
            std::views::iota(0uz, board_width_)
        )
    )
    {
        mine_field_view_[row, column].position = {
            .row = row,
            .column = column
        };
    }
}

void MinesweeperApp::update(Timer::DeltaTimeType deltaTime)
{
    if (game_over_) return;
    updateBoard();
}

void MinesweeperApp::draw()
{
    drawBoard();
}

void MinesweeperApp::handleInput()
{
    if (const auto& result = input_system_.getClick(engine::platform::EMouseButton::MOUSE_LEFT))
    {
        openCell(screenToBoard(result->position));
    }
    if (const auto& result = input_system_.getClick(engine::platform::EMouseButton::MOUSE_RIGHT))
    {
        toggleFlag(screenToBoard(result->position));
    }
}

void MinesweeperApp::openCell(GridPos position)
{
    if (const auto [row, column] = position; gridInTheBoard({.row = row, .column = column}))
    {
        auto& grid = mine_field_view_[row, column];

        if (!mines_generated_)
        {
            initialOpenCell(row, column);
            generateMines();
            forEachNeighbor(row, column,[this](const GridInfo& neighbor_info) -> void
            {
                if (neighbor_info.adjacent_mine == 0)
                {
                    expandZeroArea(neighbor_info.position.row, neighbor_info.position.column);
                }
            });
            mines_generated_ = true;
        }

        if (grid.state == GridState::CLOSED)
        {
            if (grid.is_mine)
            {
                grid.state = GridState::OPENED;
                game_over_ = true;
                return;
            }
            grid.state = GridState::OPENED;
            if (grid.adjacent_mine == 0)
            {
                expandZeroArea(row, column);
            }
        }
    }
}

void MinesweeperApp::initialOpenCell(const std::size_t row, const std::size_t column)
{
    mine_field_view_[row, column].state = GridState::OPENED;

    forEachNeighbor(row, column, [this](GridInfo& neighbor_info) -> void
    {
        neighbor_info.state = GridState::OPENED;
    });
}

void MinesweeperApp::expandZeroArea(const std::size_t row, const std::size_t column)
{
    std::queue<GridPos> pending;

    pending.push({
        .row = row,
        .column = column
    });

    while (!pending.empty())
    {
        const auto [row, column] = pending.front();
        pending.pop();

        forEachNeighbor(
            row,
            column,
            [&pending](GridInfo& neighbor_info) -> void{
                if (neighbor_info.state != GridState::CLOSED)
                {
                    return;
                }

                if (neighbor_info.is_mine)
                {
                    return;
                }

                neighbor_info.state = GridState::OPENED;

                if (neighbor_info.adjacent_mine == 0)
                {
                    pending.push(neighbor_info.position);
                }
        });
    }
}

void MinesweeperApp::toggleFlag(GridPos position)
{
    if (!gridInTheBoard(position) || game_over_)
    {
        return;
    }
    if (const auto [row, column] = position; gridInTheBoard({.row = row, .column = column}))
    {
        if (auto& grid = mine_field_view_[row, column]; grid.state == GridState::FLAGGED)
        {
            grid.state = GridState::CLOSED;
        }
        else if (grid.state == GridState::CLOSED)
        {
            grid.state = GridState::FLAGGED;
        }
    }
    if (checkWin())
    {
        game_over_ = true;
        std::println("Sweep all mines");
    }
}

void MinesweeperApp::generateMines()
{
    std::vector<std::size_t> indices(mine_field_.size());
    std::ranges::iota(indices, 0uz);
    std::erase_if(
        indices,
        [this](const auto index)
        {
            return mine_field_[index].state != GridState::CLOSED;
        }
    );
    std::ranges::shuffle(indices, random_.rng());

    for (const auto index : indices | std::views::take(mine_count_))
    {
        mine_field_[index].is_mine = true;

        const auto row = index / mine_field_view_.extent(1);
        const auto column = index % mine_field_view_.extent(1);

        forEachNeighbor(row, column, [this](GridInfo& neighbor_info) -> void
        {
            ++neighbor_info.adjacent_mine;
        });
    }
}

void MinesweeperApp::updateBoard()
{
    handleInput();
}

auto MinesweeperApp::screenToBoard(const math::Vector2 position) -> GridPos
{
    const auto row = static_cast<std::size_t>( (position.y - board_origin_.y) / cell_size_ );

    const auto column = static_cast<std::size_t>( (position.x - board_origin_.x) / cell_size_ );

    return {.row = row, .column = column};
}

bool MinesweeperApp::gridInTheBoard(const GridPos position) const
{
    return position.row < mine_field_view_.extent(0) && position.column < mine_field_view_.extent(1);
}

void MinesweeperApp::createBoard(const std::size_t width, const std::size_t height)
{
    board_width_ = width;
    board_height_ = height;

    mine_field_.resize(width * height);

    mine_field_view_ = std::mdspan{mine_field_.data(), height, width};

    for (const auto [row, column] :
        std::views::cartesian_product(
            std::views::iota(0uz, height),
            std::views::iota(0uz, width)
        )
    )
    {
        mine_field_view_[row, column].position = {
            .row = row,
            .column = column
        };
    }
}

void MinesweeperApp::drawBoard() const
{
    const auto& board_view = std::views::cartesian_product(
        std::views::iota(0uz, mine_field_view_.extent(0)),
        std::views::iota(0uz, mine_field_view_.extent(1))
    );
    for (const auto& [row, column] : board_view)
    {
        const auto&[grid_pos, is_mine, adjacent_mine, state] = mine_field_view_[row, column];

        constexpr std::string_view mine_numbers = "012345678";

        const math::Vector2 position{
            board_origin_.x + static_cast<float>(column * cell_size_),
            board_origin_.y + static_cast<float>(row * cell_size_)
        };

        const math::BaseRect rect{
            {position.x, position.y,},
            {cell_size_, cell_size_}
        };

        switch (state)
        {
            case GridState::OPENED:
            {
                if (is_mine)
                {
                    const auto text_result = app_renderer_.drawSimpleText(
                        engine::render::SimpleText2DCommand{
                            .text = "*",
                            .color = {color_white}
                        },
                        math::Transform2D{
                            .position = {position.x + cell_size_*0.27f, position.y + cell_size_*0.27f},
                        }
                    );
                    if (!text_result)
                    {
                        std::println("MineSweeperApp::drawBoard() text render failed: {}", std::to_underlying(text_result.error()));
                    }
                }
                else
                {
                    const auto rect_result = app_renderer_.drawRectangle(
                    engine::render::Rect2DCommand{
                        .rect {rect},
                        .color {color_white},
                        .filled {true}
                    },
                    math::Transform2D{
                        .position {0.0f, 0.0f}
                    }
                );
                    if (!rect_result)
                    {
                        std::println("MineSweeperApp::drawBoard() rect render failed: {}", std::to_underlying(rect_result.error()));
                    }

                    const auto text_result = app_renderer_.drawSimpleText(
                        engine::render::SimpleText2DCommand{
                            .text = mine_numbers.substr(adjacent_mine, 1)=="0"?"":mine_numbers.substr(adjacent_mine, 1),
                            .color = {color_black}
                        },
                        math::Transform2D{
                            .position = {position.x + cell_size_*0.266f, position.y + cell_size_*0.266f},
                        }
                    );
                    if (!text_result)
                    {
                        std::println("MineSweeperApp::drawBoard() text render failed: {}", std::to_underlying(text_result.error()));
                    }
                }
                break;
            }

            case GridState::FLAGGED:
            {
                const auto result = app_renderer_.drawRectangle(
                    engine::render::Rect2DCommand{
                        .rect {rect},
                        .color {color_black},
                        .filled {false}
                    },
                    math::Transform2D{
                        .position {0.0f, 0.0f}
                    }
                );
                if (!result)
                {
                    std::println("MineSweeperApp::drawBoard() failed: {}", std::to_underlying(result.error()));
                }
                const auto text_result = app_renderer_.drawSimpleText(
                    engine::render::SimpleText2DCommand{
                        .text = "F",
                        .color = {color_white}
                    },
                    math::Transform2D{
                        .position = {position.x + cell_size_*0.27f, position.y + cell_size_*0.27f},
                    }
                );
                if (!text_result)
                {
                    std::println("MineSweeperApp::drawBoard() text render failed: {}", std::to_underlying(text_result.error()));
                }
                break;
            }

            case GridState::CLOSED :
            {
                if (game_over_)
                {
                    if (is_mine)
                    {
                        const auto text_result = app_renderer_.drawSimpleText(
                            engine::render::SimpleText2DCommand{
                                .text = "*",
                                .color = {color_white}
                            },
                            math::Transform2D{
                                .position = {position.x + cell_size_*0.27f, position.y + cell_size_*0.27f},
                            }
                        );
                        if (!text_result)
                        {
                            std::println("MineSweeperApp::drawBoard() text render failed: {}", std::to_underlying(text_result.error()));
                        }
                    }
                    else if (is_mine)
                    {
                        const auto text_result = app_renderer_.drawSimpleText(
                            engine::render::SimpleText2DCommand{
                                .text = mine_numbers.substr(adjacent_mine, 1),
                                .color = {color_white}
                            },
                            math::Transform2D{
                                .position = {position.x + cell_size_*0.27f, position.y + cell_size_*0.27f},
                            }
                        );
                        if (!text_result)
                        {
                            std::println("MineSweeperApp::drawBoard() text render failed: {}", std::to_underlying(text_result.error()));
                        }
                    }
                }
                break;
            }
            default : break;
        }
    }
}

bool MinesweeperApp::checkWin() const
{
    return std::ranges::all_of(
        mine_field_,
        [](const GridInfo& grid)
        {
            return grid.is_mine == (grid.state == GridState::FLAGGED);
        }
    );
}



