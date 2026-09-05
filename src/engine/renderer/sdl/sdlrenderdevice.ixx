module;
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"

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
	        explicit SdlRenderDevice(platform::WindowObPtr window_borrowed);

	        platform::SdlRendererDeviceObPtr getRendererPtr() const;

	        static RenderCapabilities capabilities();
    };

    SdlRenderDevice::SdlRenderDevice(platform::WindowObPtr window_borrowed)
	    : renderer_ptr(
	    	SDL_CreateRenderer(window_borrowed.get(), nullptr)
	    )
    {
		//renderer_ptr = SdlRendererDevicePtr(SDL_CreateRenderer(&sdlwindow.getWindow(), nullptr), SDL_DestroyRenderer);
		if (!renderer_ptr)
		{
			auto error = std::string("Failed to create SDL renderer: ") + SDL_GetError();
			throw std::runtime_error(SDL_GetError());
		}
    }

    platform::SdlRendererDeviceObPtr SdlRenderDevice::getRendererPtr() const
    {
		return renderer_ptr;
    }

    RenderCapabilities SdlRenderDevice::capabilities()
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
