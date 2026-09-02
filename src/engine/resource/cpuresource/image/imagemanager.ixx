module;
#include "glm/vec2.hpp"

export module engine.resource.resourcemanager:texturemanager;
import engine.utilities;
import engine.resource.resourcecache;
import engine.resource.imageadapter;
import engine.resource.imageasset;
import engine.resource.resourcehandle;
import engine.resource.resourcetraits;
import engine.resource.resourceptr;
import engine.render.rendererbackend;
import engine.core.math;
import std;

export namespace engine::resource
{
	class ImageManager
	{
		private:
			using adapter = ImageAdapter;
			ResourceCache<ImageKey, ImageAsset> resource_cache_;
			
		public:
			explicit ImageManager() = default;
			~ImageManager() = default;

			ImageManager(const ImageManager&) = delete;
			ImageManager& operator=(const ImageManager&) = delete;
			ImageManager(ImageManager&&) = delete;
			ImageManager& operator=(ImageManager&&) = delete;
			
			std::expected<core::Vector2, ResourceError>  getImageSize(const ImageKey& key);
			std::expected<core::Vector2, ResourceError>  getImageSize(ImageObPtr texture_ptr) const;
			std::expected<ImageHandle, ResourceError> findImage(const ImageKey& key) const;
			std::expected<ImageHandle, ResourceError> loadImage(const ImageKey& key);
			std::expected<ImageObPtr, ResourceError> getImage(ImageHandle handle);
			std::expected<void, ResourceError> unloadImage(const ImageKey& key);
			void clearImages();                                       
	};

	std::expected<core::Vector2, ResourceError> ImageManager::getImageSize(const ImageKey& key)
	{
		if (auto handle = findImage(key))
		{
			if (auto texture_ptr = getImage(handle.value()))
			{
				return adapter::getImageSize(texture_ptr.value().get());
			}
			else
			{
				return std::unexpected(texture_ptr.error());
			}
		}
		else
		{
			return std::unexpected(handle.error());
		}
	}

	std::expected<core::Vector2, ResourceError> ImageManager::getImageSize(ImageObPtr texture_ptr) const
	{
		if (!texture_ptr) return std::unexpected(ResourceError::NULL_PTR);

		return adapter::getImageSize(texture_ptr.get());
	}

	std::expected<ImageHandle, ResourceError> ImageManager::findImage(const ImageKey& key)const
	{
		auto resource = resource_cache_.find(key);
		return resource;
	}

	std::expected<ImageHandle, ResourceError> ImageManager::loadImage(const ImageKey& key)
	{
		return resource_cache_.load(
			key, 
			 [this](const ImageKey& k)
			{
				return makeOwnRs<ImageAsset>(
					adapter::loadImage(k.path.string())
				);
			});
	}

	std::expected<ImageObPtr, ResourceError> ImageManager::getImage(ImageHandle handle)
	{
		return resource_cache_.get(handle);
	}

	std::expected<void, ResourceError> ImageManager::unloadImage(const ImageKey& key)
	{
		return resource_cache_.erase(key);
	}

	void ImageManager::clearImages()
	{
		resource_cache_.clear();
	}
};

