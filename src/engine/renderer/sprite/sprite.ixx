module;
#include <glm/glm.hpp>

export module engine.renderer.sprite;

import engine.resource.sdlresourcecache;
import engine.resource.resourcehandle;
import engine.core.math;
import std;

export namespace engine::renderer
{
	struct TextureRect
	{
		core::Vector2 position;
		core::Vector2 size;
	};
	enum class FlipMode : std::uint8_t
	{
		FLIP_NONE,                                                                  /**< Do not flip */
		FLIP_HORIZONTAL,                                                            /**< flip horizontally */
		FLIP_VERTICAL,                                                              /**< flip vertically */
		FLIP_HORIZONTAL_AND_VERTICAL = (FLIP_HORIZONTAL | FLIP_VERTICAL)    /**< flip horizontally and vertically (not a diagonal flip) */
	};
	class Sprite final 
	{
		private:
			resource::TextureHandle texture_;
			std::optional<TextureRect> source_rect_;

		public:
			Sprite() = default;
			Sprite(resource::TextureHandle texture_handle, const std::optional<TextureRect>& source_rect = std::nullopt);

			[[nodiscard]]
			resource::TextureHandle getTextureHandle() const;

			[[nodiscard]]
			const std::optional<TextureRect>& getSourceRect() const;

			void setTextureHandle(resource::TextureHandle texture);

			void setSourceRect(const std::optional<TextureRect>& source_rect);
	};

	Sprite::Sprite(resource::TextureHandle texture_handle, const std::optional<TextureRect>& source_rect)
		:	texture_(texture_handle),
			source_rect_(source_rect)
	{
	}

	resource::TextureHandle Sprite::getTextureHandle() const
	{
		return texture_;
	}

	const std::optional<TextureRect>& Sprite::getSourceRect() const
	{
		return source_rect_;
	}

	void Sprite::setTextureHandle(resource::TextureHandle texture)
	{
		texture_ = texture;
	}

	void Sprite::setSourceRect(const std::optional<TextureRect>& source_rect)
	{
		source_rect_ = source_rect;
	}

	
}
