module;

export module engine.render.rendercommandqueue;
import std;

export namespace engine::render
{
    template<typename CommandType>
    struct RenderCommandQueue
    {
		private:
			std::vector<CommandType> commands_;

	    public:
            void insert(const CommandType& command);
            void insert(CommandType&& command);

			void clear() noexcept;

			[[nodiscard]]
            std::span<const CommandType> commands() const noexcept;

			[[nodiscard]]
	        bool empty() const noexcept
			;
    };

    template <typename CommandType>
    void RenderCommandQueue<CommandType>::insert(const CommandType& command)
    {
        commands_.emplace_back(command);
    }

    template <typename CommandType>
    void RenderCommandQueue<CommandType>::insert(CommandType&& command)
    {
        commands_.emplace_back(std::move(command));
    }

    template <typename CommandType>
    void RenderCommandQueue<CommandType>::clear() noexcept
    {
	    commands_.clear();
    }

    template <typename CommandType>
    auto RenderCommandQueue<CommandType>::commands() const noexcept -> std::span<const CommandType>
    {
	    return commands_;
    }

    template <typename CommandType>
    bool RenderCommandQueue<CommandType>::empty() const noexcept
    {
	    return commands_.empty();
    }
};
