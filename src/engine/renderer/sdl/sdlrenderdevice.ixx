module;
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "spdlog/spdlog.h"

export module engine.renderer.sdlrenderdevice;
import engine.platform.sdlptr;

export namespace engine::renderer
{
    class SdlRenderDevice
    {
	    private:
	        platform::SdlRendererPtr renderer_ptr;

	    public:
	        explicit SdlRenderDevice(const platform::WindowObPtr& window_borrowed);

	        platform::SdlRendererObPtr getRendererPtr() const;
    };

    SdlRenderDevice::SdlRenderDevice(const platform::WindowObPtr& window_borrowed)
	    : renderer_ptr(
	    	platform::SdlRendererPtr(SDL_CreateRenderer(window_borrowed.get(), nullptr))
	    )
    {
		//renderer_ptr = SdlRendererPtr(SDL_CreateRenderer(&sdlwindow.getWindow(), nullptr), SDL_DestroyRenderer);
		if (!renderer_ptr)
		{
			auto error = std::string("Failed to create SDL renderer: ") + SDL_GetError();
			spdlog::error(error);
			throw std::runtime_error(SDL_GetError());
		}
    }

    platform::SdlRendererObPtr SdlRenderDevice::getRendererPtr() const
    {
		return renderer_ptr;
    }
}
