module;

export module engine.core.runtime;

import engine.core.timer;
import engine.core.appconfig;
import engine.core.eventdispatcher;
import engine.core.eventtype;
import engine.platform.sdlplatform;
import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.render.sdlrenderdevice;
import engine.render.sdlrenderer;
import engine.render.rendererservice;
import engine.render.rendererbackend;
import engine.render.framerecorder;
import engine.render.rendertypes;
import engine.resource.resourcemanager;
import engine.utilities;
import std;

export namespace engine::core
{
	template<typename App>
	concept AppInit = std::invocable<decltype(&App::init), App>;

	template<typename App>
	concept AppUpdate = std::invocable<decltype(&App::update), App>;;

	template<typename App>
	concept AppDraw =  std::invocable<decltype(&App::draw), App>;

	template<typename App>
	concept AppFunc = AppInit<App> && AppUpdate<App> && AppDraw<App>;

	template<typename  App>
	concept HasProcessEvent =
	requires(Event&& event)
	{
		std::invoke(&App::processEvent, std::declval<App>(), std::forward<Event>(event));
	};

	template<typename App> requires AppFunc<App>
	class Runtime final
	{
		private:
			platform::SdlPlatform platform_;
			platform::SdlWindow window_;
			resource::ResourceManager resource_manager_;
			render::RendererService renderer_service_;
			EventDispatcher dispatcher_;
			App app_;
			bool running_;

		public:
			bool isRunning() const noexcept
			{
				return running_;
			}

			explicit operator bool() const noexcept
			{
				return running_;
			}

			Runtime(render::ERenderBackend backend, const AppConfig& config);
			static Runtime& instance(render::ERenderBackend backend, const AppConfig& config = froth_default_app_config)
			{
				static Runtime runtime{backend, config};
				return runtime;
			}
			~Runtime()=default;

			void test();
			void init();
			void beginFrame();
			void iterate();
			void processEvent(const Event& event);
			void processEvents();
			void endFrame();
			void quit();

			auto run() -> std::expected<void, render::ERendererError>;
	};

	template<typename App> requires AppFunc<App>
	Runtime<App>::Runtime(const render::ERenderBackend backend, const AppConfig& config) :
		platform_{},
		window_{config.window_config_},
		resource_manager_{},
		renderer_service_(backend, window_.getRef(), resource_manager_),
		app_(resource_manager_, renderer_service_.frameRecorder()),
		running_(true)
	{
		Timer::init();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::test()
	{
		if (const auto result = renderer_service_.testSdlGpu(); !result)
		{
			running_ = false;
		}
	}

	template<typename App> requires AppFunc<App>
	auto Runtime<App>::run() -> std::expected<void, render::ERendererError>
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
	void Runtime<App>::init()
	{
		std::invoke_r<void>(&App::init, app_);
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
		std::invoke_r<void>(&App::update, app_);
		std::invoke_r<void>(&App::draw, app_);

		if (!renderer_service_.run()) return;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::processEvent(const Event& event)
	{
		if (std::holds_alternative<QuitEvent>(event)) running_ = false;
		if constexpr (HasProcessEvent<App>) std::invoke_r<void>(&App::processEvent, app_, event);
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::processEvents()
	{
		while (auto event = platform_.pollEvent())
		{
			processEvent(*event);
		}
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


