module;


export module engine.resource.resourcemanager;
export import :texturemanager;
import :audiomanager;
import :fontmanager;

export namespace engine::resource
{
	class ResourceManager final
	{
		private:
			TextureManager texture_manager_;
			AudioManager audio_manager_;
			FontManager font_manager_;

		public:
			ResourceManager(const platform::SdlRendererObPtr renderer_borrowed);
			~ResourceManager() = default;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;

			utilities::ObPtr<TextureManager> getTextureManager();
	};

	ResourceManager::ResourceManager(const platform::SdlRendererObPtr renderer_borrowed)
		: texture_manager_(renderer_borrowed)
	{
	}

	utilities::ObPtr<TextureManager> ResourceManager::getTextureManager()
	{
		return &texture_manager_;
	}
}
