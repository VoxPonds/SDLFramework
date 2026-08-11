module;
#include "SDL3/SDL_init.h"

export module engine.core.application;

import engine.platform.sdlwindowmanager;
import engine.renderer.sdlrenderer;
import engine.resource.sdlresourcemanager;
import engine.core.timer;

export namespace engine::core
{
	class Application final
	{
		private:
			platform::SdlWindowManager window_manager_;
			renderer::SdlRenderer renderer_manager_;
			resource::ResourceManager resource_manager_;
			Timer timer_;

	    public:
			Application();
			static Application& instance()
			{
				static Application app;
				return app;
			}
			~Application() = default;

	        void tick()const;
	        static void shutdown();
   
	};

	Application::Application() : 
		window_manager_(),
		renderer_manager_(window_manager_),
		resource_manager_(renderer_manager_)
	{
		
	}

	void Application::tick()const
	{
		renderer_manager_.renderTest();
	}

	void Application::shutdown()
	{
		SDL_Quit();
	}
}


