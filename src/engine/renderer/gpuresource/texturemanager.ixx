module;
#include "SDL3/SDL_render.h"

export module engine.render.texturemanager;

import engine.render.sdlrendereradapter;
import engine.resource.resourcecache;
import engine.resource.resourcehandle;
import engine.resource.resourceptr;
import engine.resource.resourcemanager;
import engine.resource.imageasset;
import engine.platform.sdlptr;
import std;

export namespace engine::render
{
	class TextureManager final
	{
		using TextureHandle = resource::ResourceHandle<SDL_Texture>;
		private:
			resource::ResourceCache<resource::ImageHandle, SDL_Texture> resource_cache_;
			SdlRendererAdapter renderer_adapter;
			resource::ResourceManager& cpu_Rs_Manager;

		public:
			TextureManager(SDL_Renderer& renderer_, resource::ResourceManager& manager);
			~TextureManager() = default;

			TextureManager(const TextureManager&) = delete;
			TextureManager& operator=(const TextureManager&) = delete;
			TextureManager(TextureManager&&) = delete;
			TextureManager& operator=(TextureManager&&) = delete;

			std::expected<TextureHandle, resource::EResourceError> findTexture(const resource::ImageHandle& key) const;
			std::expected<TextureHandle, resource::EResourceError> loadTexture(const resource::ImageHandle& key);
			std::expected<resource::SdlTextureObPtr, resource::EResourceError> getTexture(TextureHandle handle);
			std::expected<void, resource::EResourceError> unloadTexture(const resource::ImageHandle& key);
			void clearTextures();
	};
}

namespace engine::render
{
	TextureManager::TextureManager(SDL_Renderer& renderer_, resource::ResourceManager& manager):
	renderer_adapter(renderer_),
	cpu_Rs_Manager(manager)
	{
	}

	auto TextureManager::findTexture(const resource::ImageHandle& key) const -> std::expected<TextureHandle, resource::EResourceError>
	{
		auto handle = resource_cache_.find(key);
		return handle;
	}

	auto TextureManager::loadTexture(const resource::ImageHandle& key) -> std::expected<TextureHandle, resource::EResourceError>
	{
		std::println("LoadTexture: {}", key.getId());
		return resource_cache_.load(
			key,
			[this](const resource::ImageHandle& k)
			{
				auto image = cpu_Rs_Manager.getImage(k);
				if (!image) return resource::SdlTexturePtr{};
				auto result = renderer_adapter.loadTexture(image.value());
				if (!result) return resource::SdlTexturePtr{};
				return std::move(result.value());
			});
	}

	auto TextureManager::getTexture(TextureHandle handle) -> std::expected<resource::SdlTextureObPtr, resource::EResourceError>
	{
		return resource_cache_.get(handle);
	}

	auto TextureManager::unloadTexture(const resource::ImageHandle& key) -> std::expected<void, resource::EResourceError>
	{
		return resource_cache_.erase(key);
	}

	void TextureManager::clearTextures()
	{
		resource_cache_.clear();
	}
}
