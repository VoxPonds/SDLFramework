module;

export module engine.core.runtime;

import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.render.sdlrenderdevice;
import engine.render.sdlrenderer;
import engine.renderer.rendererservice;
import engine.render.rendererbackend;
import engine.resource.resourcemanager;
import engine.render.framerecorder;
import engine.core.timer;
import engine.utilities;

export namespace engine::core
{
	template<typename App>
	concept AppFunc = 
		requires(App& app)
		{
			app.init(), app.update(), app.render();
		};
	
	template<typename App> requires AppFunc<App>
	class Runtime final
	{
		private:
			platform::SdlWindow window_manager_;
			resource::ResourceManager resource_manager_;
			render::RendererService renderer_service_;
			Timer timer_;
			App app_;

	    public:
			Runtime();
			static Runtime& instance()
			{
				static Runtime runtime;
				return runtime;
			}
			~Runtime()=default;

			void test()const;
			void begin();
			void iterate();
			void processEvent();
			void quit();
			
			resource::ResourceManager& ResourceManager();
			render::RendererService& RendererService();
			std::expected<void, render::RendererError> run();
	};

	template<typename App> requires AppFunc<App>
	Runtime<App>::Runtime() :
		window_manager_(),
		resource_manager_(),
		renderer_service_(render::ERenderBackend::SDL_RENDERER, window_manager_.getWindowRef(), resource_manager_),
		timer_(),
		app_(ResourceManager(), RendererService().frameRecorder())
	{
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::test() const
	{
		//renderer_.renderTest();
	}

	template<typename App> requires AppFunc<App>
	std::expected<void, render::RendererError> Runtime<App>::run()
	{
		renderer_service_.beginFrame();
		processEvent();
		iterate();
		return{};
	}

	template<typename App> requires AppFunc<App>
	resource::ResourceManager& Runtime<App>::ResourceManager()
	{
		return resource_manager_;
	}

	template<typename App> requires AppFunc<App>
	render::RendererService& Runtime<App>::RendererService()
	{
		return renderer_service_;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::begin()
	{
		app_.init();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::iterate()
	{
		renderer_service_.beginFrame();
		app_.render();
		if (!renderer_service_.run()) return;
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::processEvent()
	{
		app_.update();
	}

	template<typename App> requires AppFunc<App>
	void Runtime<App>::quit()
	{
	}

}


