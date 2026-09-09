module;
#include "SDL3/SDL_events.h"

export module engine.core.runtime;

import engine.core.timer;
import engine.core.eventdispatcher;
import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.render.sdlrenderdevice;
import engine.render.sdlrenderer;
import engine.renderer.rendererservice;
import engine.render.rendererbackend;
import engine.resource.resourcemanager;
import engine.render.framerecorder;
import engine.render.rendertypes;
import engine.utilities;
import std;

export namespace engine::core
{
	template<typename App>
	concept AppFunc = 
		requires(App& app)
		{
			app.init(), app.update(), app.draw();
		};
	
	template<typename App> requires AppFunc<App>
	class Runtime final
	{
		private:
			platform::SdlWindow window_manager_;
			resource::ResourceManager resource_manager_;
			render::RendererService renderer_service_;
			EventDispatcher dispatcher_;
			App app_;
			bool running_;

		public:
			bool isRunning() const
			{
				return running_;
			}

			Runtime();
			static Runtime& instance()
			{
				static Runtime runtime;
				return runtime;
			}
			~Runtime()=default;

			void test()const;
			void init();
			void beginFrame();
			void iterate();
			void processEvent(const SDL_Event* event = nullptr);
			void endFrame();
			void quit();
			
			const resource::ResourceManager& ResourceManager()const;
			const render::RendererService& RendererService()const;
			std::expected<void, render::RendererError> run();
	};

	template<typename App> requires AppFunc<App>
	Runtime<App>::Runtime() :
		window_manager_{},
		resource_manager_{},
		renderer_service_(render::ERenderBackend::SDL_RENDERER, window_manager_.getWindowRef(), resource_manager_),
		app_(resource_manager_, renderer_service_.frameRecorder()),
		running_(true)
	{
		Timer::init();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::test() const
	{
		//renderer_.renderTest();
	}

	template<typename App> requires AppFunc<App>
	std::expected<void, render::RendererError> Runtime<App>::run()
	{
		Timer::beginFrame();
		renderer_service_.beginFrame();
		processEvent();
		iterate();
		renderer_service_.endFrame();
		Timer::endFrame();
		return{};
	}

	template<typename App> requires AppFunc<App>
	const resource::ResourceManager& Runtime<App>::ResourceManager()const
	{
		return resource_manager_;
	}

	template<typename App> requires AppFunc<App>
	const render::RendererService& Runtime<App>::RendererService()const
	{
		return renderer_service_;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::init()
	{
		app_.init();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::beginFrame()
	{
		Timer::beginFrame();
		renderer_service_.beginFrame();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::iterate()
	{
		app_.update();
		if (auto result = app_.draw(); !result) return;
		if (!renderer_service_.run()) return;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::processEvent(const SDL_Event* event)
	{
		//std::println("running:{}", isRunning());
		if (!event)
		{
			SDL_Event polled_event;
			while (SDL_PollEvent(&polled_event))
			{
				if (polled_event.type == SDL_EVENT_QUIT)
				{
					running_ = false;
				}
			}
			return;
		}
		if (event->type == SDL_EVENT_QUIT) running_ = false;

		// if (event)
		// {
		// 	if (event->type == SDL_EVENT_QUIT)
		// 		running_ = false;

		// 	return;
		// }

		// SDL_Event polled_event;
		// while (SDL_PollEvent(&polled_event))
		// {
		// 	processEvent(&polled_event);
		// }
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::endFrame()
	{
		renderer_service_.endFrame();
		Timer::endFrame();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::quit()
	{
	}

}


