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

	template<>
	struct SdlDeleterTraits<SDL_GPUDevice>
	{
		static constexpr auto destroy_func = SDL_DestroyGPUDevice;
	};

	template<>
	struct SdlDeleterTraits<SDL_GPURenderPass>
	{
		static constexpr auto destroy_func = SDL_EndGPURenderPass;
	};

	template<typename T>
	struct SdlDeleter
	{
		void operator()(T* ptr) const noexcept
		{
			if (ptr) SdlDeleterTraits<T>::destroy_func(ptr);
		}
	};

	template<auto DestroyFunc>
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
	using SdlRendererDeviceBrPtr = utilities::BrPtr<SDL_Renderer>;

	using SdlWindowPtr = SdlPtr<SDL_Window>;
	using SdlWindowObPtr = utilities::ObPtr<SDL_Window>;
	using SdlWindowBrPtr = utilities::BrPtr<SDL_Window>;

	using SdlGpuDevicePtr = SdlPtr<SDL_GPUDevice>;
	using SdlGpuDeviceObPtr = utilities::ObPtr<SDL_GPUDevice>;
	using SdlGpuDeviceBrPtr = utilities::BrPtr<SDL_GPUDevice>;

	using SdlGpuCommandBufferObPtr =  utilities::ObPtr<SDL_GPUCommandBuffer>;
	using SdlGpuCommandBufferBrPtr = utilities::BrPtr<SDL_GPUCommandBuffer>;

	using SdlGpuRenderPassPtr = SdlPtr<SDL_GPURenderPass>;
	using SdlGpuRenderPassObPtr = utilities::ObPtr<SDL_GPURenderPass>;
	using SdlGpuRenderPassBrPtr = utilities::BrPtr<SDL_GPURenderPass>;

}
