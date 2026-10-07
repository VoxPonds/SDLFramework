module;
#include "SDL3/SDL_render.h"

export module engine.resource.resourceptr;
import engine.resource.imageasset;
import engine.utilities;
import engine.resource.resourcetraits;
import std;

export namespace engine::resource
{
	template<typename T, auto Deleter>
	using CustomResourcePtr = std::unique_ptr<T, FuncDeleter<Deleter>>;

	template<typename T>
	using ResourcePtr = std::unique_ptr<T, typename ResourceTraits<T>::Deleter>;

	template<typename T>
	struct GetElementType;

	template<typename T>
	struct GetElementType<ResourcePtr<T>>
	{
		using element_type = T;
	};

	template<typename T, typename... Args> requires std::constructible_from<T, Args...>
	auto makeOwnRs(Args&&... args) -> ResourcePtr<T>
	{
		return ResourcePtr<T>{new T{std::forward<Args>(args)...}};
	}
	
	using ImagePtr = ResourcePtr<ImageAsset>;
	using ImageObPtr = utilities::ObserverPtr<ImageAsset>;

	using SdlTexturePtr = ResourcePtr<SDL_Texture>;
	using SdlTextureObPtr = utilities::ObPtr<SDL_Texture>;

	using SdlSurfacePtr = ResourcePtr<SDL_Surface>;
	using SdlSurfaceObPtr = utilities::ObPtr<SDL_Surface>;

	using SdlGpuShaderPtr = ResourcePtr<SDL_GPUShader>;
	using SdlGpuShaderObPtr = utilities::ObPtr<SDL_GPUShader>;

	using SdlGpuBufferPtr = ResourcePtr<SDL_GPUBuffer>;
	using SdlGpuBufferObPtr = utilities::ObPtr<SDL_GPUBuffer>;
	using SdlGpuBufferBrPtr = utilities::BrPtr<SDL_GPUBuffer>;

	using SdlGpuTransferBufferPtr = ResourcePtr<SDL_GPUTransferBuffer>;
	using SdlGpuTransferBufferObPtr = utilities::ObPtr<SDL_GPUTransferBuffer>;

	using SdlGpuGraphicsPipelinePtr = ResourcePtr<SDL_GPUGraphicsPipeline>;
	using SdlGpuGraphicsPipelineObPtr = utilities::ObPtr<SDL_GPUGraphicsPipeline>;
	using SdlGpuGraphicsPipelineBrPtr = utilities::BrPtr<SDL_GPUGraphicsPipeline>;

	using SdlGpuTextureObPtr = utilities::ObPtr<SDL_GPUTexture>;
	using SdlGpuTextureBrPtr = utilities::BrPtr<SDL_GPUTexture>;

}
