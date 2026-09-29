module;
#include "SDL3/SDL_video.h"

export module engine.render.rendererservice;

import engine.render.rendererbackend;
import engine.render.sdlrenderdevice;
import engine.render.rendertypes;
import engine.render.sdlrenderer;
import engine.render.framerecorder;
import engine.render.sdlgpurenderer;
import engine.render.sdlgpudevice;
import engine.render.sdlgpucommandcontext;
import engine.resource.resourcemanager;
import engine.platform.sdlptr;
import engine.utilities;
import std;

export namespace engine::render
{
	template<typename Func>
	concept BackendVisitor =
		std::invocable<Func&&, SdlRenderer&>&&
		std::invocable<Func&&, SdlGpuRenderer&>;
	struct RendererService
	{
		using RendererDevice = std::variant<SdlRenderDevice, SdlGpuDevice>;
		using Renderer = std::variant<SdlRenderer, SdlGpuRenderer>;
		private:
			RendererDevice renderer_device;
			Renderer renderer;
			FrameRecorder recorder_;

			static auto createDevice(ERenderBackend type, SDL_Window& window_ref) -> RendererDevice;
			auto generateBackend(resource::ResourceManager& manager_ref) -> Renderer;

		public:
			RendererService(ERenderBackend type, SDL_Window& window_ref, resource::ResourceManager& manager_ref);
			FrameRecorder& frameRecorder();
			template<BackendVisitor Func>
			auto visitBackend(Func&& func) -> decltype(auto);

			void beginFrame();
			std::expected<void, ERendererError> run();
			std::expected<void, EGpuError> testSdlGpu();
			void endFrame();
	};

	RendererService::RendererService(const ERenderBackend type, SDL_Window& window_ref, resource::ResourceManager& manager_ref):
		renderer_device(createDevice(type, window_ref)),
		renderer(generateBackend(manager_ref))
	{
	}

	FrameRecorder& RendererService::frameRecorder()
	{
		return recorder_;
	}

	auto RendererService::createDevice(const ERenderBackend type, SDL_Window &window_ref) -> RendererDevice
	{
		switch(type)
		{
			case ERenderBackend::SDL_RENDERER:
			{
				return RendererDevice{std::in_place_type<SdlRenderDevice>,window_ref};
			}
			case ERenderBackend::SDL_GPU:
			{
				return RendererDevice{std::in_place_type<SdlGpuDevice>,window_ref};
			}
			default:
			{
				std::unreachable();
			}
		}
	}

	auto RendererService::generateBackend(resource::ResourceManager& manager_ref) -> Renderer
	{
		return std::visit(
			[&manager_ref]<typename T>(T&& device) -> Renderer
			{
				using DT = std::remove_cvref_t<T>;
				if constexpr(std::is_same_v<DT, SdlRenderDevice>)
				{
					return Renderer{
						std::in_place_type<SdlRenderer>,
						device.get(), manager_ref
					};
				}
				else if constexpr(std::is_same_v<DT, SdlGpuDevice>)
				{
					return Renderer{
						std::in_place_type<SdlGpuRenderer>,
						utilities::borrow(device), manager_ref
					};
				}
				std::unreachable();
			},
			renderer_device
		);
	}

	template<BackendVisitor Func>
	auto RendererService::visitBackend(Func&& func) -> decltype(auto)
	{
		return std::visit(
			std::forward<Func>(func),
			renderer
		);
	}

	void RendererService::beginFrame()
	{
		recorder_.beginFrame();
	}

	std::expected<void, ERendererError> RendererService::run()
	{
		return std::visit(
			[this](auto& backend)
			{
				return backend.render(recorder_.Data());
			},
			renderer
		);
	}

	std::expected<void, EGpuError> RendererService::testSdlGpu()
	{
		const auto sdl_gpu_renderer = std::get_if<SdlGpuRenderer>(&renderer);
		return sdl_gpu_renderer->renderTest();
	}

	void RendererService::endFrame()
	{
	}
}
