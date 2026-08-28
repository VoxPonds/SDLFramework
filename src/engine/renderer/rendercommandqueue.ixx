module;

export module engine.renderer.renderer:rendercommandqueue;
import std;

export namespace engine::renderer
{
    template<typename Command>
    struct RenderCommandQueue
    {
		private:
			std::vector<Command> commands_;

	    public:
            void submit(const Command& command);
            void submit(Command&& command);

			void clear() noexcept;

			[[nodiscard]]
            std::span<const Command> commands() const noexcept;

			[[nodiscard]]
	        bool empty() const noexcept
			;
    };

    template <typename Command>
    void RenderCommandQueue<Command>::submit(const Command& command)
    {
        commands_.emplace_back(command);
    }

    template <typename Command>
    void RenderCommandQueue<Command>::submit(Command&& command)
    {
        commands_.emplace_back(std::move(command));
    }

    template <typename Command>
    void RenderCommandQueue<Command>::clear() noexcept
    {
	    commands_.clear();
    }

    template <typename Command>
    auto RenderCommandQueue<Command>::commands() const noexcept -> std::span<const Command>
    {
	    return commands_;
    }

    template <typename Command>
    bool RenderCommandQueue<Command>::empty() const noexcept
    {
	    return commands_.empty();
    }
};
