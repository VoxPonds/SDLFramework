module;

export module engine.resource.resourcemanager;
import :texturemanager;
import :audiomanager;
import :fontmanager;
import engine.render.rendererbackend;

export namespace engine::resource
{
	enum class EResourceType
	{
		
	};

	class ResourceManager final
	{
		private:
			ImageManager image_manager_;
			AudioManager audio_manager_;
			FontManager font_manager_;

		public:
			ResourceManager() = default;
			~ResourceManager() = default;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;

			std::expected<ImageObPtr, ResourceError> getImage(ImageHandle handle);
			std::expected<core::Vector2, ResourceError> getImageSize(ImageObPtr texture_ptr) const;
			std::expected<ImageHandle, ResourceError> loadImage(const ImageKey& key);
	};


	std::expected<ImageObPtr, ResourceError> ResourceManager::getImage(ImageHandle handle)
	{
		return image_manager_.getImage(handle);
	}

	std::expected<core::Vector2, ResourceError> ResourceManager::getImageSize(ImageObPtr texture_ptr) const
	{
		return image_manager_.getImageSize(texture_ptr);
	}

	std::expected<ImageHandle, ResourceError> ResourceManager::loadImage(const ImageKey& key)
	{
		return image_manager_.loadImage(key);
	}
}
