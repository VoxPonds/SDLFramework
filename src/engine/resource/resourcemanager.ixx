module;


export module engine.resource.sdlresourcemanager;
import :texturemanager;
import :audiomanager;
import :fontmanager;
import engine.renderer.sdlrenderer;

export namespace engine::resource
{
	class ResourceManager final
	{
		private:
			TextureManager texture_manager_;
			AudioManager audio_manager_;
			FontManager font_manager_;

		public:
			ResourceManager(const renderer::SdlRenderer& renderer_manager_ref);
			~ResourceManager() = default;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;
	};

	ResourceManager::ResourceManager(const renderer::SdlRenderer& renderer_manager_ref) 
		: texture_manager_(renderer_manager_ref.getSDLRendererRef())
	{
	}
}
