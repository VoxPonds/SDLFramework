module;
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"

export module engine.platform.sdlptr;
import std.compat;

export namespace engine::platform
{
	template<typename T>
	struct SdlDeleterTraits;

	template<>
	struct SdlDeleterTraits<SDL_Window>
	{
		static constexpr auto destroy_func = SDL_DestroyWindow;
	};

	template<>
	struct SdlDeleterTraits<SDL_Renderer>
	{
		static constexpr auto destroy_func = SDL_DestroyRenderer;
	};

	template<>
	struct SdlDeleterTraits<SDL_Texture>
	{
		static constexpr auto destroy_func = SDL_DestroyTexture;
	};

	template<typename T>
	struct SdlDeleter
	{
		void operator()(T* ptr) const
		{
			if (ptr) SdlDeleterTraits<T>::destroy_func(ptr);
		}
	};

	template<auto DestroyFunc> //NTTP 
	struct SdlFuncDeleter
	{
		template<typename T>
		void operator()(T* ptr) const
		{
			if (ptr) DestroyFunc(ptr);
		}
	};

	template<typename T>
	class ObserverPtr
	{
		private:
			T* ptr_ = nullptr;

		public:
			ObserverPtr() = default;
			ObserverPtr(T* ptr) : ptr_(ptr) {}
			template<typename D>
			ObserverPtr(const std::unique_ptr<T, D>& ptr)
				: ptr_(ptr.get()){}
			//~ObserverPtr() = delete;

			T* get() const { return ptr_; }
			T& operator*() const { return *ptr_; }
			T* operator->() const { return ptr_; }

			explicit operator bool() const
			{
				return ptr_ != nullptr;
			}
	};

	template<typename T>
	using SdlPtr = std::unique_ptr<T, SdlDeleter<T>>;

	template<typename T, typename D>
	ObserverPtr(std::unique_ptr<T, D>) -> ObserverPtr<T>;

	template<typename T>
	using SdlObPtr = ObserverPtr<T>;

	
	using RendererPtr = SdlPtr<SDL_Renderer>;
	using RendererObPtr = SdlObPtr<SDL_Renderer>;

	using WindowPtr = SdlPtr<SDL_Window>;
	using WindowObPtr = SdlObPtr<SDL_Window>;

	using TexturePtr = SdlPtr<SDL_Texture>;
	using TextureObPtr = SdlObPtr<SDL_Texture>;

}
