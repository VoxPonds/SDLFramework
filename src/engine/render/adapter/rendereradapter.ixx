module;
#include "SDL3/SDL_render.h"

export module engine.render.sdlrendereradapter;

import engine.resource.imageadapter;
import engine.resource.imageasset;
import engine.resource.resourceptr;
import engine.core.math;
import engine.platform.sdlptr;
import engine.render.framerecorder;
import std;

export namespace engine::render
{
	class SdlRendererAdapter
	{
		private:
	        platform::SdlRendererDeviceObPtr renderer_;
			static SDL_PixelFormat ConvertFormat(resource::PixelFormat format);
			std::expected<resource::SdlTexturePtr, ERendererError> translate(resource::ImageObPtr image);

		public:
			SdlRendererAdapter(platform::SdlRendererDeviceBrPtr renderer);
            std::expected<resource::SdlTexturePtr, ERendererError> loadTexture(resource::ImageObPtr image);
	};
}

namespace engine::render
{
	SdlRendererAdapter::SdlRendererAdapter(const platform::SdlRendererDeviceBrPtr renderer):
	renderer_(renderer.get())
	{
	}

	SDL_PixelFormat SdlRendererAdapter::ConvertFormat(resource::PixelFormat format)
	{
		return static_cast<SDL_PixelFormat>(format);
	}

	std::expected<resource::SdlTexturePtr, ERendererError> SdlRendererAdapter::translate(resource::ImageObPtr image)
	{
		const SDL_PixelFormat format = ConvertFormat(image->format);

		SDL_Texture* texture = SDL_CreateTexture(
			renderer_.get(),
			format,
			SDL_TEXTUREACCESS_STATIC,
			image->width,
			image->height
		);

		if (!texture) return std::unexpected(ERendererError::CREATE_TEXTURE_FAILED);

		const std::size_t bytes_per_pixel = SDL_BYTESPERPIXEL(format);
		const std::size_t row_size = static_cast<std::size_t>(image->width) * bytes_per_pixel;

		if (!SDL_UpdateTexture(
			texture,
			nullptr,
			image->pixels.data(),
			static_cast<int>(row_size))
		)
		{
			SDL_DestroyTexture(texture);
			return std::unexpected(ERendererError::UPDATE_TEXTURE_FAILED);
		}

		return resource::SdlTexturePtr{texture};
	}

	std::expected<resource::SdlTexturePtr, ERendererError> SdlRendererAdapter::loadTexture(resource::ImageObPtr image)
	{
		return translate(image);
	}
}
