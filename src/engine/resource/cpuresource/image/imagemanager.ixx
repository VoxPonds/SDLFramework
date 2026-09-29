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
			
			std::expected<core::Vector2, EResourceError>  getImageSize(const ImageKey& key);
			std::expected<core::Vector2, EResourceError>  getImageSize(ImageObPtr texture_ptr) const;
			std::expected<ImageHandle, EResourceError> findImage(const ImageKey& key) const;
			std::expected<ImageHandle, EResourceError> loadImage(const ImageKey& key);
			std::expected<ImageObPtr, EResourceError> getImage(ImageHandle handle);
			std::expected<void, EResourceError> unloadImage(const ImageKey& key);
			void clearImages();                                       
	};

	std::expected<core::Vector2, EResourceError> ImageManager::getImageSize(const ImageKey& key)
	{
		if (auto handle = findImage(key))
		{
			if (auto texture_ptr = getImage(handle.value()))
			{
				return adapter::getImageSize(utilities::ObPtr(texture_ptr.value().get()));
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
};

namespace engine::resource
{
	std::expected<core::Vector2, EResourceError> ImageManager::getImageSize(ImageObPtr texture_ptr) const
	{
		if (!texture_ptr) return std::unexpected(EResourceError::NULL_PTR);

		return adapter::getImageSize(utilities::ObPtr(texture_ptr.get()));
	}

	std::expected<ImageHandle, EResourceError> ImageManager::findImage(const ImageKey& key)const
	{
		auto resource = resource_cache_.find(key);
		return resource;
	}

	std::expected<ImageHandle, EResourceError> ImageManager::loadImage(const ImageKey& key)
	{
		return resource_cache_.load(
			key,
			 [this](const ImageKey& k) -> ResourcePtr<ImageAsset>
			{
				auto result = adapter::loadImage(k.path.string());
				if (!result) return nullptr;
				return makeOwnRs<ImageAsset>(
					std::move(result.value())
				);
			});
	}

	std::expected<ImageObPtr, EResourceError> ImageManager::getImage(ImageHandle handle)
	{
		return resource_cache_.get(handle);
	}

	std::expected<void, EResourceError> ImageManager::unloadImage(const ImageKey& key)
	{
		return resource_cache_.erase(key);
	}

	void ImageManager::clearImages()
	{
		resource_cache_.clear();
	}
}

