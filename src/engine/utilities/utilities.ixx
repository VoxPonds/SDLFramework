module;

export module engine.utilities;
import std;


export namespace engine::utilities
{
	template<typename T>
	void hashCombine(std::size_t& seed, const T& value) noexcept
	{
		seed ^= std::hash<T>{}(value)
			+ static_cast<std::size_t>(0x9e3779b9)
			+ (seed << 6)
			+ (seed >> 2);
	}

	template<typename...Ts>
	concept hashConstructible = (std::is_default_constructible_v<std::hash<Ts>> && ...);

	template<typename T>
	concept hashableType = 
		requires
		{
			{ std::hash<T>{}(std::declval<const T&>()) } -> std::convertible_to<std::size_t>;
		};

	template<typename... Ts>
	concept hashableTypes = 
		requires
		{(
		 	std::is_convertible_v < 
				decltype(std::hash<Ts>{}(std::declval<const Ts&>())), 
				std::size_t 
			> && ...
		);};

	template<hashableTypes... Ts>
	std::size_t makeHash(const Ts&... values) noexcept
	{
		std::size_t seed = 0;
		(hashCombine(seed, values), ...);
		return seed;
	}

	template<typename T>
	struct ObserverPtr
	{
		private:
			T* ptr_ = nullptr;

		public:
			ObserverPtr() = default;
			ObserverPtr(T* ptr) : ptr_(ptr) {}
			ObserverPtr(T& ref) : ptr_(&ref) {}
			template<typename D>
			ObserverPtr(const std::unique_ptr<T, D>& ptr)
				: ptr_(ptr.get()) {
			}
			~ObserverPtr() = default;
			T* get() const { return ptr_; }
			T& operator*() const { return *ptr_; }
			T* operator->() const { return ptr_; }

			explicit operator bool() const
			{
				return ptr_ != nullptr;
			}
	};

	template<typename T, typename D>
	ObserverPtr(std::unique_ptr<T, D>) -> ObserverPtr<T>;

	template<typename T>
	using ObPtr = ObserverPtr<T>;
}
