module;
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "spdlog/spdlog.h"

export module engine.render.sdlrenderdevice;
import engine.platform.sdlptr;

export namespace engine::render
{
    class SdlRenderDevice
    {
	    private:
	        platform::SdlRendererDevicePtr renderer_ptr;

	    public:
	        explicit SdlRenderDevice(platform::WindowObPtr window_borrowed);

	        platform::SdlRendererDeviceObPtr getRendererPtr() const;
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
			spdlog::error(error);
			throw std::runtime_error(SDL_GetError());
		}
    }

    platform::SdlRendererDeviceObPtr SdlRenderDevice::getRendererPtr() const
    {
		return renderer_ptr;
    }
}
