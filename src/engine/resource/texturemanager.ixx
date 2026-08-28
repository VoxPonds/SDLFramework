module;
#include "SDL3_image/SDL_image.h"
#include "glm/vec2.hpp"

export module engine.resource.resourcemanager:texturemanager;
import engine.utilities;
import engine.platform.sdlptr;
import engine.resource.sdlresourcecache;
import engine.resource.resourcehandle;
import engine.core.math;
import std;


export namespace engine::resource
{
	class TextureManager
	{
		private:
			platform::SdlRendererObPtr renderer_;
			SdlResourceCache<TextureKey, SDL_Texture> resource_cache_;

		public:
			explicit TextureManager(platform::SdlRendererObPtr renderer_borrowed);
			~TextureManager() = default;

			TextureManager(const TextureManager&) = delete;
			TextureManager& operator=(const TextureManager&) = delete;
			TextureManager(TextureManager&&) = delete;
			TextureManager& operator=(TextureManager&&) = delete;

			std::expected<core::Vector2,ResourceError>  getTextureSize(const TextureKey& key);
			static std::expected<core::Vector2, ResourceError>  getTextureSize(utilities::ObPtr<SDL_Texture> texture_ptr);
			std::expected<TextureHandle, ResourceError> findTexture(const TextureKey& key)const;
			std::expected<TextureHandle, ResourceError> loadTexture(const TextureKey& key);
			std::expected<utilities::ObPtr<SDL_Texture>, ResourceError> getTexture(ResourceHandle<SDL_Texture> handle);
			std::expected<void, ResourceError> unloadTexture(const TextureKey& key);
			void clearTextures();                                       
	};

	TextureManager::TextureManager(platform::SdlRendererObPtr renderer_borrowed) : renderer_(renderer_borrowed)
	{
	}

	std::expected<core::Vector2, ResourceError> TextureManager::getTextureSize(const TextureKey& key)
	{
		if (auto handle = findTexture(key))
		{
			if (auto texture_ptr = getTexture(handle.value()))
			{
				core::Vector2 size;
				SDL_GetTextureSize(texture_ptr.value().get(), &size.x, &size.y);
				return size;
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

	std::expected<core::Vector2, ResourceError> TextureManager::getTextureSize(utilities::ObPtr<SDL_Texture> texture_ptr)
	{
		if (!texture_ptr) return std::unexpected(ResourceError::NullPtr);
		core::Vector2 size;
		SDL_GetTextureSize(texture_ptr.get(), &size.x, &size.y);
		return size;
	}
	

	std::expected<TextureHandle, ResourceError> TextureManager::findTexture(const TextureKey& key)const
	{
		auto resource = resource_cache_.find(key);
		return resource;
	}

	std::expected<TextureHandle, ResourceError> TextureManager::loadTexture(const TextureKey& key)
	{
		return resource_cache_.load(
			key, 
			 [this](const TextureKey& k)
			{
				return platform::TexturePtr(IMG_LoadTexture(renderer_.get(), k.path.string().c_str()));
			});
	}

	std::expected<utilities::ObPtr<SDL_Texture>, ResourceError> TextureManager::getTexture(ResourceHandle<SDL_Texture> handle)
	{
		return resource_cache_.get(handle);
	}

	std::expected<void, ResourceError> TextureManager::unloadTexture(const TextureKey& key)
	{
		return resource_cache_.erase(key);
	}

	void TextureManager::clearTextures()
	{
		resource_cache_.clear();
	}
};

