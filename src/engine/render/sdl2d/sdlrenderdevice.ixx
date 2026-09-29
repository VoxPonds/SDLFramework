module;
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

export module engine.render.sdlrenderdevice;
import engine.platform.sdlptr;
import engine.render.rendertypes;
import std;

export namespace engine::render
{
    class SdlRenderDevice
    {
	    private:
	        platform::SdlRendererDevicePtr renderer_ptr;
    		RenderCapabilities capabilities_;

	    public:
	        explicit SdlRenderDevice(SDL_Window& window_borrowed);
    		~SdlRenderDevice() = default;

	        platform::SdlRendererDeviceObPtr get() const;

	        static RenderCapabilities getCapabilities();
    };
}

namespace engine::render
{
	SdlRenderDevice::SdlRenderDevice(SDL_Window& window_borrowed)
	: renderer_ptr(
		SDL_CreateRenderer(&window_borrowed, nullptr)
	)
	{
		//renderer_ptr = SdlRendererDevicePtr(SDL_CreateRenderer(&sdlwindow.getWindow(), nullptr), SDL_DestroyRenderer);
		if (!renderer_ptr)
		{
			const auto error = std::string("Failed to create SDL renderer: ") + SDL_GetError();
			throw std::runtime_error(SDL_GetError());
		}
	}

	platform::SdlRendererDeviceObPtr SdlRenderDevice::get() const
	{
		return platform::SdlRendererDeviceObPtr(renderer_ptr);
	}

	RenderCapabilities SdlRenderDevice::getCapabilities()
	{
		return RenderCapabilities{
			.supports_3d = false,
			.supports_compute = false,
			.supports_msaa = false,
			.supports_bindless = false,
			.supports_texture_compression = false,
		};
	}
}
