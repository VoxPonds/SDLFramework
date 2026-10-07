module;
#include "SDL3/SDL_gpu.h"

export module engine.render.sdlgpurenderpass;

import engine.platform.sdlptr;
import engine.resource.resourceptr;
import std;

export namespace engine::render
{
    class SdlGpuRenderPass
    {
        private:
            platform::SdlGpuRenderPassPtr m_pass_ {};

        public:
            explicit SdlGpuRenderPass(SDL_GPURenderPass* pass);

            void bindPipeline(resource::SdlGpuGraphicsPipelineBrPtr pipeline) const;

            void bindVertexBuffer(resource::SdlGpuBufferBrPtr buffer) const;

            void draw(std::uint32_t vertex_count) const;
    };
}

namespace engine::render
{
    SdlGpuRenderPass::SdlGpuRenderPass(SDL_GPURenderPass* pass)
        : m_pass_(pass)
    {
    }

    void SdlGpuRenderPass::bindPipeline(const resource::SdlGpuGraphicsPipelineBrPtr pipeline) const
    {
        SDL_BindGPUGraphicsPipeline(m_pass_.get(),&pipeline.get());
    }

    void SdlGpuRenderPass::bindVertexBuffer(const resource::SdlGpuBufferBrPtr buffer) const
    {
        const SDL_GPUBufferBinding binding{
            .buffer = &buffer.get(),
            .offset = 0
        };

        SDL_BindGPUVertexBuffers(m_pass_.get(),0,&binding,1);
    }

    void SdlGpuRenderPass::draw(const std::uint32_t vertex_count) const
    {
        SDL_DrawGPUPrimitives(m_pass_.get(),vertex_count,1,0,0);
    }
}
