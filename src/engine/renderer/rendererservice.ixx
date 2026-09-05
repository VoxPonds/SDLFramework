module;
#include "SDL3/SDL_video.h"

export module engine.renderer.rendererservice;
import engine.render.rendererbackend;
import engine.render.sdlrenderdevice;
import engine.render.rendertypes;
import engine.render.sdlrenderer;
import engine.resource.resourcemanager;
import engine.render.framerecorder;
import engine.platform.sdlptr;
import engine.utilities;
import std;


export namespace engine::render
{
	struct RendererService
	{
		private:
			SdlRenderDevice renderer_device;
			std::unique_ptr<IRendererBackend> renderer;
			FrameRecorder recorder_;
			auto generateBackend(ERenderBackend type, SDL_Window& window_ref,
				resource::ResourceManager& manager_ref)const -> std::unique_ptr<IRendererBackend>;

		public:
			IRendererBackend& backend() const;
			RendererService(ERenderBackend type, SDL_Window& window_ref, resource::ResourceManager& manager_ref);
			FrameRecorder& frameRecorder();

			void beginFrame();
			std::expected<void, RendererError> run();
			void endFrame();
	};

	RendererService::RendererService(ERenderBackend type, SDL_Window& window_ref, resource::ResourceManager& manager_ref)
	:
		renderer_device(window_ref),
		renderer(generateBackend(type, window_ref, manager_ref))
	{
	}

	FrameRecorder& RendererService::frameRecorder()
	{
		return recorder_;
	}

	auto RendererService::generateBackend(ERenderBackend type, SDL_Window& window_ref,
	                                      resource::ResourceManager& manager_ref) const -> std::unique_ptr<IRendererBackend>
	{
		switch (type)
		{
			case ERenderBackend::SDL_RENDERER:
				return std::make_unique<SdlRenderer>(renderer_device.getRendererPtr(), manager_ref);

			//case ERenderBackend::BGFX:
			//	return std::make_unique<BGFXRenderDevice>(window_ptr);
			default:
				std::unreachable();
		}
	}

	IRendererBackend& RendererService::backend() const
	{
		return *renderer.get();
	}

	void RendererService::beginFrame()
	{
		recorder_.beginFrame();
	}

	std::expected<void, RendererError> RendererService::run()
	{
		return backend().render(recorder_.Data());
	}

	void RendererService::endFrame()
	{
	}
}
