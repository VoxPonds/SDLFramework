module;
#include <SDL3_image/SDL_image.h>
#include "glm/vec2.hpp"
#include "spdlog/spdlog.h"

export module engine.resource.sdlresourcemanager:texturemanager;
import engine.utilities;
import engine.platform.sdlptr;
import engine.resource.sdlresourcecache;
import engine.resource.resourcehandle;


export namespace engine::resource
{
	class TextureManager
	{
		private:
			platform::RendererObPtr renderer_;
			SdlResourceCache<TextureKey, SDL_Texture> resource_cache_;

		public:
			explicit TextureManager(platform::RendererObPtr renderer_ref);
			~TextureManager() = default;

			TextureManager(const TextureManager&) = delete;
			TextureManager& operator=(const TextureManager&) = delete;
			TextureManager(TextureManager&&) = delete;
			TextureManager& operator=(TextureManager&&) = delete;

			ResourceHandle<SDL_Texture> findTexture(const TextureKey& key)const;
			ResourceHandle<SDL_Texture> loadTexture(const TextureKey& key);  
			glm::vec2 getTextureSize(const TextureKey& key);   
			void unloadTexture(const TextureKey& key);  
			void clearTextures();                                       
	};

	TextureManager::TextureManager(platform::RendererObPtr renderer_ref) : renderer_(renderer_ref)
	{
	}

	ResourceHandle<SDL_Texture> TextureManager::findTexture(const TextureKey& key)const
	{
		auto resource = resource_cache_.find(key);
		return resource;
	}

	ResourceHandle<SDL_Texture> TextureManager::loadTexture(const TextureKey& key)
	{
		return resource_cache_.load(
			key, 
			[this](const TextureKey& k)
			{
				return platform::TexturePtr(IMG_LoadTexture(renderer_.get(), k.path.c_str()));
			});
	}

	void TextureManager::unloadTexture(const TextureKey& key)
	{
		resource_cache_.erase(key);
	}

	void TextureManager::clearTextures()
	{
		resource_cache_.clear();
	}
};

