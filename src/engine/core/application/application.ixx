module;

export module engine.core.application;

import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.renderer.sdlrenderdevice;
import engine.renderer.sdlrenderer;
import engine.renderer.renderer;
import engine.resource.resourcemanager;
import engine.core.timer;
import engine.utilities;



export namespace engine::core
{
	class Application final
	{
		private:
			platform::SdlWindow window_manager_;
			renderer::SdlRenderDevice renderer_device_;
			resource::ResourceManager resource_manager_;
			renderer::SdlRenderer renderer_;
			Timer timer_;

	    public:
			Application();
			static Application& instance()
			{
				static Application app;
				return app;
			}
			~Application()=default;

			void test()const;
	        void run()const;
			utilities::ObPtr<resource::ResourceManager> getResourceManager();
			utilities::ObPtr<renderer::Renderer> getRenderer();

		private:
			void begin();
			void iterate();
			void processEvent();
			void quit();
	};

}


