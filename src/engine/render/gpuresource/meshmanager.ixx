module;
#include <SDL3/SDL_gpu.h>

export module engine.render.meshmanager;

import engine.resource.resourcehandle;
import engine.resource.resourcecache;
import engine.resource.resourcemanager;
import engine.render.mesh;
import std;

export namespace engine::render
{
    struct GpuResource
    {
        SDL_GPUBuffer* vertex_buffer;
        SDL_GPUBuffer* index_buffer;
    };

    class MeshManager final
    {
        using MeshHandle = resource::ResourceHandle<MeshData>;
        private:
            /*resource::ResourceCache<MeshHandle, GpuResource> m_resource_pool_;*/
            resource::ResourceManager& cpu_Rs_Manager;

        /*public:
            MeshManager(SDL_Renderer& renderer_, resource::ResourceManager& manager);
            ~MeshManager() = default;

            MeshManager(const MeshManager&) = delete;
            MeshManager& operator=(const MeshManager&) = delete;
            MeshManager(MeshManager&&) = delete;
            MeshManager& operator=(MeshManager&&) = delete;

            std::expected<TextureHandle, resource::EResourceError> findMesh(const resource::ImageHandle& key) const;
            std::expected<TextureHandle, resource::EResourceError> loadMesh(const resource::ImageHandle& key);
            std::expected<resource::SdlTextureObPtr, resource::EResourceError> getMesh(TextureHandle handle);
            std::expected<void, resource::EResourceError> unloadMesh(const resource::ImageHandle& key);
            void clearTextures();*/
    };
}

namespace engine::render
{

}
