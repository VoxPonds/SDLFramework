import engine.core.application;
import engine.resource.resourcemanager;
import engine.renderer.sdlrenderer;
import engine.renderer.renderer;

namespace engine::core
{
	Application::Application() :
		window_manager_(),
		renderer_device_(window_manager_.getWindowPtr()),
		resource_manager_(renderer_device_.getRendererPtr()),
		renderer_(renderer_device_.getRendererPtr(), resource_manager_.getTextureManager())

	{
	}

	void Application::test() const
	{
		renderer_.renderTest();
	}

	void Application::run()const
	{
	}

	utilities::ObPtr<resource::ResourceManager> Application::getResourceManager()
	{
		return resource_manager_;
	}

	utilities::ObPtr<renderer::Renderer> Application::getRenderer()
	{
		return renderer_;
	}

	void Application::begin()
	{
	}

	void Application::iterate()
	{
	}

	void Application::processEvent()
	{
	}

	void Application::quit()
	{
	}
}


