module;
#include <cassert>

export module engine.utilities;
import std;

export namespace engine::utilities
{
	template <bool condition>
	constexpr void assertion(std::string_view message)
	{
		static_assert(condition);
	}

	template<bool b>
	struct Assertion
	{
		explicit Assertion(std::bool_constant<b>) {}
		void operator()() const
		{
			assertion<b>();
		}
	};

	template<bool b>
	Assertion(std::bool_constant<b>) -> Assertion<b>;

	constexpr void assertion(const bool condition)
	{
		if (condition) return;
		if consteval { std::abort(); }
		assert(condition);
	}

	template<typename T>
	constexpr void hashCombine(std::size_t& seed, const T& value) noexcept
	{
		seed ^= std::hash<T>{}(value)
			+ static_cast<std::size_t>(0x9e3779b9)
			+ (seed << 6)
			+ (seed >> 2);
	}

	template<typename... Ts>
	concept HashConstructible =
		(
			std::is_default_constructible_v<std::hash<Ts>> && ...
		);

	template<typename T>
	concept HashableType =
		requires
		{
			{ std::hash<T>{}(std::declval<const T&>()) } -> std::same_as<std::size_t>;
		};

	template<typename... Ts>
	concept HashableTypes =
		(
			std::same_as<decltype(std::hash<Ts>{}(std::declval<const Ts&>())), std::size_t> && ...
		);

	template<HashableTypes... Ts> requires HashConstructible<Ts...>
	constexpr std::size_t makeHash(const Ts&... values) noexcept
	{
		std::size_t seed {0};
		(hashCombine(seed, values), ...);
		return seed;
	}

	template<typename T>
	struct ObserverPtr
	{
		private:
			T* ptr_ {nullptr};

		public:
			ObserverPtr() = default;
			explicit ObserverPtr(T* ptr) noexcept : ptr_(ptr) {}
			explicit ObserverPtr(T& ref) noexcept : ptr_(std::addressof(ref)) {}
			template<typename D>
			explicit ObserverPtr(const std::unique_ptr<T, D>& ptr) noexcept
				: ptr_(ptr.get()) {
			}
			~ObserverPtr() = default;
			T* get() const noexcept { return ptr_; }
			T** put() noexcept {return std::addressof(ptr_);}
			T& operator*() const noexcept { return *ptr_; }
			T* operator->() const noexcept { return ptr_; }
			explicit operator bool() const noexcept
			{
				return ptr_ != nullptr;
			}
	};

	template<typename T>
	ObserverPtr<T> observe(T* ptr) noexcept
	{
		return ObserverPtr<T>(ptr);
	}

	template<typename T, typename D>
	ObserverPtr(std::unique_ptr<T, D>) -> ObserverPtr<T>;

	template <typename T>
	struct BorrowedPtr
	{
		private:
			T* ptr_ {nullptr};

		public:
			explicit BorrowedPtr(T& ref) noexcept : ptr_(std::addressof(ref)) {}
			explicit BorrowedPtr(T&&) = delete;
			explicit BorrowedPtr(std::nullptr_t) = delete;
			explicit BorrowedPtr(T* ptr) noexcept : ptr_(ptr)
			{
				assertion(ptr != nullptr && "Require non-null pointer");
			}
			BorrowedPtr(const BorrowedPtr&) = default;
			BorrowedPtr& operator=(const BorrowedPtr&) = default;
			BorrowedPtr(BorrowedPtr&&) noexcept = default;
			BorrowedPtr& operator=(BorrowedPtr&&) noexcept = default;
			~BorrowedPtr() = default;
			T& get() const noexcept { return *ptr_; }
			T* operator->() const noexcept { return ptr_; }
			T& operator*() const noexcept { return *ptr_; }
	};

	template<typename T>
	BorrowedPtr<T> borrow(T& ref) noexcept
	{
		return BorrowedPtr<T>(ref);
	}

	template<typename T>
	using ObPtr = ObserverPtr<T>;

	template<typename T>
	using BrPtr = BorrowedPtr<T>;
}

export namespace util = engine::utilities;
