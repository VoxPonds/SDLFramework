module;
#include "SDL3/SDL_render.h"

export module engine.platform.sdlptr;
import engine.utilities;
import std;

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
	using SdlPtr = std::unique_ptr<T, SdlDeleter<T>>;

	
	using SdlRendererDevicePtr = SdlPtr<SDL_Renderer>;
	using SdlRendererDeviceObPtr = utilities::ObPtr<SDL_Renderer>;

	using WindowPtr = SdlPtr<SDL_Window>;
	using WindowObPtr = utilities::ObPtr<SDL_Window>;


}
