module;
#include "SDL3_image/SDL_image.h"

export module engine.resource.imageadapter;

import engine.platform.sdlptr;
import engine.resource.imageasset;
import engine.resource.resourceptr;
import engine.resource.resourcehandle;
import engine.render.rendererbackend;
import engine.utilities;
import engine.core.math;
import std;

export namespace engine::resource
{
	enum class TranslateError : std::uint8_t
	{
		NOT_EXIST_TYPE,
		CANNOT_TRANSLATE
	};

	class ImageAdapter
	{
		private:
			static PixelFormat ConvertFormat(SDL_PixelFormat format);
			static std::expected<ImageAsset, EResourceError> translate(SdlSurfaceObPtr surface);

		public:
			ImageAdapter() = delete;

			static core::Vector2 getImageSize(utilities::ObPtr<ImageAsset> ptr);
			static std::expected<ImageAsset, EResourceError> loadImage(std::string_view path);
			
	};

	core::Vector2 ImageAdapter::getImageSize(utilities::ObPtr<ImageAsset> ptr)
	{
		return core::Vector2{ ptr->width,ptr->height };
	}

	std::expected<ImageAsset, EResourceError> ImageAdapter::loadImage(std::string_view path)
	{
		SdlSurfacePtr surface{
			IMG_Load(std::string{path}.c_str())
		};
		if (!surface)
		{
			std::println("IMG_Load failed");
			std::println("SDL error: {}", SDL_GetError());
			std::println("cwd = {}", std::filesystem::current_path().string());
			std::println("image = {}", path);
			return std::unexpected(EResourceError::LOAD_FAILED);
		}

		return translate(surface);
	}

	PixelFormat ImageAdapter::ConvertFormat(SDL_PixelFormat format)
	{
		return static_cast<PixelFormat>(format);
	}

	std::expected<ImageAsset, EResourceError> ImageAdapter::translate(SdlSurfaceObPtr surface)
	{
		ImageAsset image;
		/*if (!surface)
		{
			return std::unexpected(EResourceError::NULL_PTR);
		}*/
		image.width = surface->w;
		image.height = surface->h;
		image.format = ConvertFormat(surface->format);

		const std::size_t bytes_per_pixel = SDL_BYTESPERPIXEL(surface->format);

		const std::size_t row_size = static_cast<std::size_t>(image.width) * bytes_per_pixel;

		const std::size_t size = row_size * static_cast<std::size_t>(image.height);
		image.pixels.resize(size);

		auto* src = static_cast<const std::byte*>(surface->pixels);

		for (int y = 0; y < image.height; ++y)
		{
			std::memcpy(
				image.pixels.data() + y * row_size,
				src + y * surface->pitch,
				row_size
			);
		}

		return image;
		//SDL_ConvertPixels();
		//SDL_ConvertSurface();
	}
}
