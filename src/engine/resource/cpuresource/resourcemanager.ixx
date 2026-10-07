module;

export module engine.resource.resourcemanager;
import :texturemanager;
import :audiomanager;
import :fontmanager;

import engine.render.rendererbackend;

export namespace engine::resource
{
	class ResourceManager final
	{
		private:
			ImageManager m_image_manager_;
			AudioManager m_audio_manager_;
			FontManager m_font_manager_;

		public:
			ResourceManager() = default;
			~ResourceManager() = default;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;

			std::expected<ImageObPtr, EResourceError> getImage(ImageHandle handle);
			std::expected<math::Vector2, EResourceError> getImageSize(ImageObPtr texture_ptr) const;
			std::expected<ImageHandle, EResourceError> loadImage(const ImageKey& key);
	};
}

namespace engine::resource
{
	std::expected<ImageObPtr, EResourceError> ResourceManager::getImage(const ImageHandle handle)
	{
		return m_image_manager_.getImage(handle);
	}

	std::expected<math::Vector2, EResourceError> ResourceManager::getImageSize(const ImageObPtr texture_ptr) const
	{
		return m_image_manager_.getImageSize(texture_ptr);
	}

	std::expected<ImageHandle, EResourceError> ResourceManager::loadImage(const ImageKey& key)
	{
		return m_image_manager_.loadImage(key);
	}
}
