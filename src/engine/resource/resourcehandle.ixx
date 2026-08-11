module;

export module engine.resource.resourcehandle;
import std.compat;

export namespace engine::resource
{
    template<typename Tag>
    struct ResourceHandle 
    {
	    public:
	        using ValueType = std::uint32_t;
	        static constexpr ValueType invalid_value = std::numeric_limits<ValueType>::max();

	    private:
	        ValueType id_ = invalid_value;
			ValueType generation = 0;

	    public:
	        constexpr ResourceHandle() noexcept = default;

	        explicit constexpr ResourceHandle(ValueType id, ValueType generation) noexcept
	            : id_(id), generation(generation)
	        {
	        }

	        [[nodiscard]]
	        constexpr bool isValid() const noexcept 
	        {
	            return id_ != invalid_value;
	        }

	        [[nodiscard]]
	        constexpr ValueType getId() const noexcept 
	        {
	            return id_;
	        }

	        constexpr explicit operator bool() const noexcept
	        {
	            return isValid();
	        }

	        friend constexpr bool operator==(ResourceHandle,ResourceHandle) noexcept = default;
    };
}
