module;
#include <glm/glm.hpp>

export module engine.render.sprite;

import engine.resource.resourcecache;
import engine.resource.resourcehandle;
import engine.core.math;
import std;

export namespace engine::render
{
	struct ImageRect
	{
		math::Vector2 position;
		math::Vector2 size;
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
			resource::ImageHandle image_;
			std::optional<ImageRect> source_rect_;

		public:
			Sprite() = default;
			Sprite(resource::ImageHandle image_handle, const std::optional<ImageRect>& source_rect = std::nullopt);
			~Sprite() = default;

			[[nodiscard]]
			resource::ImageHandle getImageHandle() const;

			[[nodiscard]]
			const std::optional<ImageRect>& getSourceRect() const;

			void setImageHandle(resource::ImageHandle texture);

			void setSourceRect(const std::optional<ImageRect>& source_rect);
	};
}

namespace engine::render
{
	Sprite::Sprite(resource::ImageHandle image_handle, const std::optional<ImageRect>& source_rect)
	:	image_(image_handle),
		source_rect_(source_rect)
	{
	}

	resource::ImageHandle Sprite::getImageHandle() const
	{
		return image_;
	}

	const std::optional<ImageRect>& Sprite::getSourceRect() const
	{
		return source_rect_;
	}

	void Sprite::setImageHandle(resource::ImageHandle texture)
	{
		image_ = texture;
	}

	void Sprite::setSourceRect(const std::optional<ImageRect>& source_rect)
	{
		source_rect_ = source_rect;
	}
}
