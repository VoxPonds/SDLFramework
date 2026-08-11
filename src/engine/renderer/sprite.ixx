module;
#include "SDL3/SDL_rect.h"
#include "SDL3_image/SDL_image.h"

export module engine.renderer.sprite;
import std.compat;
import engine.resource.sdlresourcecache;
import engine.resource.resourcehandle;


export namespace engine::renderer
{
	using TextureHandle = resource::ResourceHandle<SDL_Texture>;

	class Sprite final 
	{
		private:
			TextureHandle texture_;
			std::optional<SDL_FRect> source_rect_;

		public:
			Sprite(TextureHandle texture, const std::optional<SDL_FRect>& source_rect = std::nullopt);

			[[nodiscard]]
			TextureHandle getTexture() const;

			[[nodiscard]]
			const std::optional<SDL_FRect>& getSourceRect() const;

			[[nodiscard]]
			bool isFlipped() const;

			void setTexture(TextureHandle texture);

			void setSourceRect(const std::optional<SDL_FRect>& source_rect);

			void setFlipped(bool flipped);
	};

	Sprite::Sprite(TextureHandle texture, const std::optional<SDL_FRect>& source_rect)
		:	texture_(texture),
			source_rect_(source_rect)
	{
	}

	TextureHandle Sprite::getTexture() const
	{
		return texture_;
	}

	const std::optional<SDL_FRect>& Sprite::getSourceRect() const
	{
		return source_rect_;
	}

	void Sprite::setTexture(TextureHandle texture)
	{
		texture_ = texture;
	}

	void Sprite::setSourceRect(const std::optional<SDL_FRect>& source_rect)
	{
		source_rect_ = source_rect;
	}

	
}
