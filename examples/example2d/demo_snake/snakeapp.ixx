module;

export module example2d.snakeapp;

import engine.core.eventtype;
import engine.core.math;
import engine.core.timer;
import engine.core.appconfig;
import engine.render.framedata;
import engine.render.framerecorder;
import engine.render.apprenderer;
import engine.resource.resourcemanager;
import engine.platform.inputsystem;
import engine.platform.inputcode;
import engine.utilities;
import std;

export
{
    enum class InputContextType : std::uint8_t
    {
        GAMEPLAY,
        MENU,
        PAUSE,
    };

    enum class SnakeAction : std::uint8_t
    {
        ACTION_UP,
        ACTION_LEFT,
        ACTION_DOWN,
        ACTION_RIGHT,
    };

    enum class Direction : std::uint8_t
    {
        UP,
        LEFT,
        DOWN,
        RIGHT
    };

    struct GridPos
    {
        int x {};
        int y {};

        friend bool operator==(const GridPos&, const GridPos&) = default;
    };

    struct Food
    {
        GridPos position {};
        std::vector<GridPos> shape {};
    };

    struct Snake
    {
        std::deque<GridPos> segments {};
        Direction direction_ {};
        Direction next_direction_ {direction_};
        bool direction_pending_ {false};
    };

    inline constexpr engine::core::BaseColor white{
        .r {1.0f},
        .g {1.0f},
        .b {1.0f},
        .a {1.0f}
    };

    struct SnakeApp
    {
        using SnakeInputMapping = engine::platform::InputMappingList<SnakeAction>;
        using SnakeInputSystem = engine::platform::InputSystem<SnakeAction>;
        static consteval auto appConfig() -> engine::core::AppConfig;
        inline static constinit engine::core::AppConfig app_config_ {};

        private:
            static constexpr int board_width {10};
            static constexpr int board_height {10};
            static constexpr int cell_size_ {32};
            inline static float move_interval {0.15f};
            float move_timer_ {0.0f};

            engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
            engine::render::AppRenderer app_renderer_;
            SnakeInputMapping input_mapping;
            SnakeInputSystem input_system_;

        public:
            SnakeApp(engine::resource::ResourceManager& resource_manager_borrowed, engine::render::FrameRecorder& recorder);
            void init();
            void beginFrame();
            void processEvent(const engine::core::Event& event);
            void update();
            void draw();
            void endFrame();

        private:
            Snake snake_;
            Food food_;
            bool game_over_;
            std::mt19937 rng_ {std::random_device{}()};
            void moveSnake();
            void spawnFood();
            bool containsSnake(GridPos position) const;
            bool isOpposite(Direction current, Direction next) const;
            void drawFood();
            void drawSnake();
    };
}

consteval auto SnakeApp::appConfig() -> engine::core::AppConfig
{
    return engine::core::AppConfig{
        .window_config_ {
            .width {board_width * cell_size_},
            .height {board_height * cell_size_},
            .title {"Demo Snake"},
            .flags {16},
        }
    };
}

static SnakeApp::SnakeInputMapping mappingConfig()
{
    using namespace engine::platform;
    using namespace input;

    return SnakeApp::SnakeInputMapping {
        { SnakeAction::ACTION_UP, {
            {
                pressed(EInputCode::KEY_W) |
                pressed(EInputCode::KEY_UP) |
                pressed(EInputCode::KEY_SPACE) >> pressed(EInputCode::KEY_SPACE)
            }, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_LEFT,{
            { {pressed(EInputCode::KEY_A)}, {pressed(EInputCode::KEY_LEFT)} }, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_DOWN, {
            { {pressed(EInputCode::KEY_S)}, {pressed(EInputCode::KEY_DOWN)} }, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_RIGHT, {
            { {pressed(EInputCode::KEY_D)}, {pressed(EInputCode::KEY_RIGHT)} }, MODE_TOGGLE}
        },
    };
}

SnakeApp::SnakeApp(engine::resource::ResourceManager& resource_manager_borrowed, engine::render::FrameRecorder& recorder) :
    resource_manager_borrowed_(resource_manager_borrowed),
    app_renderer_(recorder),
    input_mapping(mappingConfig()),
    input_system_(input_mapping),
    snake_(), food_(), game_over_(false)
{
    app_config_ = appConfig();
}

void SnakeApp::init()
{
    snake_ = {
        .segments {
            {5, 5},
            {4, 5},
            {3, 5},
            {2, 5}
        },
        .direction_ {Direction::DOWN}
    };

    spawnFood();
}

void SnakeApp::beginFrame()
{
}

void SnakeApp::processEvent(const engine::core::Event& event)
{
    input_system_.processEvent(event);
}

void SnakeApp::update()
{
    if (game_over_) return;
    if (!snake_.direction_pending_)
    if (input_system_.getActionEvent(SnakeAction::ACTION_UP))
    {
        if (!isOpposite(snake_.direction_, Direction::UP))
        {
            snake_.next_direction_ = Direction::UP;
            snake_.direction_pending_ = true;
        }
    }
    else if (input_system_.getActionEvent(SnakeAction::ACTION_LEFT))
    {
        if (!isOpposite(snake_.direction_, Direction::LEFT))
        {
            snake_.next_direction_ = Direction::LEFT;
            snake_.direction_pending_ = true;
        }
    }
    else if (input_system_.getActionEvent(SnakeAction::ACTION_DOWN))
    {
        if (!isOpposite(snake_.direction_, Direction::DOWN))
        {
            snake_.next_direction_ = Direction::DOWN;
            snake_.direction_pending_ = true;
        }
    }
    else if (input_system_.getActionEvent(SnakeAction::ACTION_RIGHT))
    {
        if (!isOpposite(snake_.direction_, Direction::RIGHT))
        {
            snake_.next_direction_ = Direction::RIGHT;
            snake_.direction_pending_ = true;
        }
    }

    move_timer_ += engine::core::Timer::deltaTime();

    if (move_timer_ >= move_interval)
    {
        move_timer_ -= move_interval;
        snake_.direction_ = snake_.next_direction_;
        snake_.direction_pending_ = false;
        moveSnake();
    }

    input_system_.reset();
}
void SnakeApp::draw()
{
    drawFood();
    drawSnake();
}

void SnakeApp::endFrame()
{
}

void SnakeApp::moveSnake()
{
    GridPos new_head {snake_.segments.front()};

    switch (snake_.direction_)
    {
        case Direction::UP:
            --new_head.y;
            break;

        case Direction::LEFT:
            --new_head.x;
            break;

        case Direction::DOWN:
            ++new_head.y;
            break;

        case Direction::RIGHT:
            ++new_head.x;
            break;
    }

    if (new_head.x < 0)
        new_head.x = board_width - 1;
    else if (new_head.x >= board_width)
        new_head.x = 0;

    if (new_head.y < 0)
        new_head.y = board_height - 1;
    else if (new_head.y >= board_height)
        new_head.y = 0;

    const bool ate_food = new_head == food_.position;

    if (!ate_food)
    {
        snake_.segments.pop_back();
    }

    if (containsSnake(new_head))
    {
        std::println("Eat your body");
        game_over_ = true;
        return;
    }

    snake_.segments.push_front(new_head);

    if (ate_food)
    {
        move_interval -= move_interval * 0.01;
        move_interval = std::max(0.05f, move_interval);
        spawnFood();
    }
}

void SnakeApp::spawnFood()
{
    std::uniform_int_distribution x_distribution{
        0,
        board_width - 1
    };

    std::uniform_int_distribution y_distribution{
        0,
        board_height - 1
    };

    do
    {
        food_ = {
            .position{
                x_distribution(rng_),
                y_distribution(rng_)
            },
            .shape = {
                {0,0}
            }
        };
    }
    while (containsSnake(food_.position));
}

bool SnakeApp::containsSnake(const GridPos position) const
{
    return std::ranges::find(snake_.segments, position) != snake_.segments.end();
}

bool SnakeApp::isOpposite(Direction current, Direction next) const
{
    return
        (current == Direction::UP    && next == Direction::DOWN) ||
        (current == Direction::DOWN  && next == Direction::UP) ||
        (current == Direction::LEFT  && next == Direction::RIGHT) ||
        (current == Direction::RIGHT && next == Direction::LEFT);
}

void SnakeApp::drawFood()
{
    for (const auto&[x, y] : food_.shape)
    {
        const GridPos cell{
            .x {food_.position.x + x},
            .y {food_.position.y + y}
        };
        const auto result = app_renderer_.drawRectangle(
            engine::render::DrawRect2DCommand{
                .rect {
                    .position {
                        cell.x * cell_size_,
                        cell.y * cell_size_
                    },
                    .size {cell_size_, cell_size_}
                },
                .color {white},
                .filled {true}
            },
            engine::core::Transform2D{
                .position {0.0f, 0.0f},
            }
        );
        if (!result)
        {
            std::println("SnakeApp::drawFood() failed: {}", std::to_underlying(result.error()));
        }
    }
}

void SnakeApp::drawSnake()
{
    for (const auto&[x, y] : snake_.segments)
    {
        const auto result = app_renderer_.drawRectangle(
            engine::render::DrawRect2DCommand{
                .rect {
                    .position {
                        x * cell_size_,
                        y * cell_size_
                    },
                    .size {
                        cell_size_,
                        cell_size_
                    }
                },
                .color {white},
                .filled {true}
            },
            engine::core::Transform2D{
                .position {0.0f, 0.0f}
            }
        );
        if (!result)
        {
            std::println("SnakeApp::drawSnake() failed: {}", std::to_underlying(result.error()));
        }
    }
}








