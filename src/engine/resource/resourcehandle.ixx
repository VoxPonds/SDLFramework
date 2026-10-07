module;
#include <limits>

export module engine.resource.resourcehandle;
import engine.resource.imageasset;
import std;
import engine.render.mesh;

export namespace engine::resource
{
	enum class EResourceError : std::uint8_t
	{
		NOT_FOUND,
		INVALID_HANDLE,
		STALE_HANDLE,
		NULL_PTR,
		INDEX_OUT_OF_RANGE,
		LOAD_FAILED,
		ALREADY_LOADED,
		EXCEPTION
	};

    template<typename Tag>
    struct ResourceHandle 
    {
			using ValueType = std::uint64_t;
			using IdType = std::uint32_t;
			using GenType = std::uint32_t;
			static constexpr auto invalid_value = std::numeric_limits<ValueType>::max();

	    private:
			static constexpr auto id_bits = std::numeric_limits<IdType>::digits;
			static constexpr auto generation_bits = std::numeric_limits<ValueType>::digits - id_bits;
			static constexpr auto id_mask = (1ull << id_bits) - 1;
			ValueType handle_value_ = invalid_value;

	    public:
	        constexpr ResourceHandle() noexcept = default;

	        constexpr ResourceHandle(IdType id, GenType generation) noexcept
	            : handle_value_( id | static_cast<ValueType>(generation) << id_bits)
	        {
	        }

	        [[nodiscard]]
	        constexpr bool isValid() const noexcept 
	        {
	            return handle_value_ != invalid_value;
	        }

			[[nodiscard]]
			constexpr auto getHandleValue() const noexcept
			{
				return handle_value_;
			}

			[[nodiscard]]
			constexpr auto getId() const noexcept
			{
				return static_cast<IdType>(handle_value_ & id_mask);
			}

			[[nodiscard]]
			constexpr auto getGeneration() const noexcept
			{
				return static_cast<GenType>(handle_value_ >> id_bits);
			}

	        [[nodiscard]]
	        constexpr auto getIdAndGeneration() const noexcept 
	        {
	            return std::pair(static_cast<IdType>(handle_value_ & id_mask), static_cast<GenType>(handle_value_ >> id_bits));
	        }

	        constexpr explicit operator bool() const noexcept
	        {
	            return isValid();
	        }

			friend constexpr bool operator==(ResourceHandle, ResourceHandle) noexcept = default;
    };

	using ImageHandle = ResourceHandle<ImageAsset>;

}
