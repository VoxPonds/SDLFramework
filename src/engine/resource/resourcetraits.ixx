module;
#include <filesystem>

#include "SDL3/SDL_render.h"

export module engine.resource.resourcetraits;
import engine.resource.imageasset;
import engine.resource.resourcehandle;
import engine.utilities;
import std;

export namespace engine::resource
{
    template<typename T>
    struct KeyHash;

    struct ImageKey
    {
        std::filesystem::path path;
        bool operator==(const ImageKey&) const = default;
    };

    template<>
    struct KeyHash<ImageKey>
    {
        size_t operator()(const ImageKey& key) const noexcept
        {
            return utilities::makeHash(key.path);//key.path.generic_str
        }
    };

    template<>
    struct KeyHash<ImageHandle>
    {
        size_t operator()(const ImageHandle& key) const noexcept
        {
            return utilities::makeHash(key.getHandleValue());//key.path.generic_str
        }
    };

	template<typename Resource>
	struct ResourceTraits;

	template<typename T>
	struct DeleterTraits;

	template<>
	struct DeleterTraits<ImageAsset>
	{
		static constexpr auto destroy_func = std::default_delete<ImageAsset>{};
	};

	template<>
	struct DeleterTraits<SDL_Renderer>
	{
		static constexpr auto destroy_func = SDL_DestroyRenderer;
	};

	template<>
	struct DeleterTraits<SDL_Texture>
	{
		static constexpr auto destroy_func = SDL_DestroyTexture;
	};

	template<>
	struct DeleterTraits<SDL_Surface>
	{
		static constexpr auto destroy_func = SDL_DestroySurface;
	};

	template<typename T>
	struct Deleter
	{
		void operator()(T* ptr) const
		{
			if (ptr) DeleterTraits<T>::destroy_func(ptr);
		}
	};

	template<auto DestroyFunc>
	struct FuncDeleter
	{
		template<typename T>
		void operator()(T* ptr) const
		{
			if (ptr) DestroyFunc(ptr);
		}
	};

	template<>
	struct ResourceTraits<ImageAsset>
	{
		using Key = ImageKey;
		using Hash = KeyHash<Key>;
		using Deleter = Deleter<ImageAsset>;
	};

	template<>
	struct ResourceTraits<SDL_Texture>
	{
		using Key = ImageHandle;
		using Hash = KeyHash<Key>;
		using Deleter = Deleter<SDL_Texture>;
	};

	template<>
	struct ResourceTraits<SDL_Surface>
	{
		using Deleter = Deleter<SDL_Surface>;
	};
}
