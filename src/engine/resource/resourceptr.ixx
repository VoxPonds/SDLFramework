module;
#include "SDL3/SDL_render.h"

export module engine.resource.resourceptr;
import engine.resource.imageasset;
import engine.utilities;
import engine.resource.resourcetraits;
import std;

export namespace engine::resource
{
	template<typename T>
	using ResourcePtr = std::unique_ptr<T, typename ResourceTraits<T>::Deleter>;

	template<typename T, typename... Args>
	ResourcePtr<T> makeOwnRs(Args&&... args)
	{
		return ResourcePtr<T>{
			new T{
				std::forward<Args>(args)...
			}
		};
	}
	
	using ImagePtr = ResourcePtr<ImageAsset>;
	using ImageObPtr = utilities::ObserverPtr<ImageAsset>;

	using SdlTexturePtr = ResourcePtr<SDL_Texture>;
	using SdlTextureObPtr = utilities::ObPtr<SDL_Texture>;

	using SdlSurfacePtr = ResourcePtr<SDL_Surface>;
	using SdlSurfaceObPtr = utilities::ObPtr<SDL_Surface>;


}
