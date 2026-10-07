module;

export module engine.core.runtime;

import engine.core.timer;
import engine.core.appconfig;
import engine.core.eventdispatcher;
import engine.core.eventtype;
import engine.core.appcontext;
import engine.platform.sdlplatform;
import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.platform.inputsystem;
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
	concept AppConstruct = std::constructible_from<App, AppContext&>;

	template<typename App>
	concept AppConfigConstexpr = std::invocable<decltype(&App::config)>;

	template<typename App>
	concept AppInit = std::invocable<decltype(&App::init), App>;

	template<typename App>
	concept AppUpdate = std::invocable<decltype(&App::update), App, Timer::DeltaTimeType>;

	template<typename App>
	concept AppDraw =  std::invocable<decltype(&App::draw), App>;

	template<typename App>
	concept AppFunc = AppConstruct<App> && AppConfigConstexpr<App> && AppInit<App> && AppUpdate<App> && AppDraw<App>;

	template<typename  App>
	concept HasProcessEvent = requires(Event&& event)
	{
		std::invoke(&App::processEvent, std::declval<App>(), std::forward<Event>(event));
	};

	template<typename App> requires AppFunc<App>
	class Runtime final
	{
		private:
			platform::SdlPlatform m_platform_;
			platform::SdlWindow m_window_;
			platform::InputSystem<> m_mono_input_system_;
			resource::ResourceManager m_resource_manager_;
			render::RendererService m_renderer_service_;
			EventDispatcher m_dispatcher_;
			AppContext m_app_context_;
			App m_app_;
			bool m_running_;

		public:
			Runtime(render::ERenderBackend backend, const AppConfig& config);
			static Runtime& instance(render::ERenderBackend backend, const AppConfig& config = froth_default_app_config)
			{
				static Runtime runtime{backend, config};
				return runtime;
			}
			//~Runtime() = default;

			void test();

			void init();

			void beginFrame();

			void processEvent(const Event& event);

			void processEvents();

			void iterate();

			void endFrame();

			auto createInputSystem() -> decltype(auto);

			[[maybe_unused]]
			void quit();

			[[maybe_unused]]
			auto run() -> std::expected<void, render::ERendererError>;

			bool isRunning() const noexcept("") { return m_running_; }
			explicit operator bool() const noexcept("") { return m_running_; }
	};

	template<typename App> requires AppFunc<App>
	Runtime<App>::Runtime(const render::ERenderBackend backend, const AppConfig& config) : m_platform_{},
		m_window_{config.window_config_},
		m_mono_input_system_(config),
		m_resource_manager_{},
		m_renderer_service_(backend, m_window_.getRef(), m_resource_manager_),
		m_app_context_(m_mono_input_system_, m_renderer_service_.frameRecorder(), m_resource_manager_),
		m_app_(m_app_context_),
		m_running_(true)
	{
		m_platform_.observeWindow(util::borrow(m_window_.getRef()));
		Timer::init();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::test()
	{
		if (const auto result = m_renderer_service_.testSdlGpu(); !result)
		{
			m_running_ = false;
		}
	}

	template<typename App> requires AppFunc<App>
	auto Runtime<App>::run() -> std::expected<void, render::ERendererError>
	{
		Timer::beginFrame();
		m_renderer_service_.beginFrame();
		processEvents();
		iterate();
		m_renderer_service_.endFrame();
		Timer::endFrame();
		return{};
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::init()
	{
		std::invoke_r<void>(&App::init, m_app_);
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::beginFrame()
	{
		Timer::beginFrame();
		m_renderer_service_.beginFrame();
	}

	template<typename App> requires AppFunc<App>
		void Runtime<App>::processEvent(const Event& event)
	{
		if (std::holds_alternative<QuitEvent>(event)) m_running_ = false;
		if constexpr (HasProcessEvent<App>) std::invoke_r<void>(&App::processEvent, m_app_, event);
		else m_mono_input_system_.processEvent(event);
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::processEvents()
	{
		while (auto event = m_platform_.pollEvent())
		{
			processEvent(*event);
		}
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::iterate()
	{
		std::invoke_r<void>(&App::update, m_app_, Timer::deltaTime());
		m_mono_input_system_.reset();
		std::invoke_r<void>(&App::draw, m_app_);

		if (!m_renderer_service_.run()) return;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::endFrame()
	{
		m_renderer_service_.endFrame();
		Timer::endFrame();
	}

	template<typename App> requires AppFunc<App>
	auto Runtime<App>::createInputSystem() -> decltype(auto)
	{
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::quit()
	{
	}

}


