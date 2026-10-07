module;
#include "SDL3/SDL_gpu.h"

module engine.render.sdlgpucommandcontext;

import engine.resource.resourcetraits;

namespace engine::render
{
    SdlGpuCommandContext::SdlGpuCommandContext(const platform::SdlGpuDeviceBrPtr device,
        const platform::SdlGpuCommandBufferBrPtr command_buffer):
        device_(device.get()),
        command_buffer_(command_buffer.get())
    {
    }

    auto SdlGpuCommandContext::uploadBufferBytes(const resource::SdlGpuBufferBrPtr gpu_buffer,
        const std::span<const std::byte> byte_data) const -> std::expected<void, EGpuError>
    {

        const auto byte_size = byte_data.size_bytes();
        if (byte_size > std::numeric_limits<std::uint32_t>::max())
        {
            std::println("BUFFER_SIZE_TOO_LARGE: {}",SDL_GetError());
            return std::unexpected(EGpuError::BUFFER_SIZE_TOO_LARGE);
        }

        const SDL_GPUTransferBufferCreateInfo transfer_info{
            .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
            .size = static_cast<std::uint32_t>(byte_size),
            //.props =
        };

        const resource::SdlGpuTransferBufferPtr transfer_buffer = {
            SDL_CreateGPUTransferBuffer(device_.get(), &transfer_info),
            resource::ResourceTraits<SDL_GPUTransferBuffer>::Deleter(device_.get())
        };
        if (!transfer_buffer)
        {
            std::println("SDL_CreateGPUTransferBuffer failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::GPU_TRANSFER_BUFFER_CREATE_FAILED);
        }

        const auto mapped = SDL_MapGPUTransferBuffer(device_.get(), transfer_buffer.get(),true);
        if (!mapped)
        {
            std::println("SDL_MapGPUTransferBuffer failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::GPU_TRANSFER_BUFFER_MAPPING_CREATE_FAILED);
        }

        std::memcpy(mapped, byte_data.data(), byte_size);
        SDL_UnmapGPUTransferBuffer(device_.get(), transfer_buffer.get());

        auto copy_pass = beginCopyPass();
        if (!copy_pass)
        {
            std::println("SDL_BeginGPUCopyPass failed: {}",SDL_GetError());
            return std::unexpected(copy_pass.error());
        }
        const SDL_GPUTransferBufferLocation source{
            .transfer_buffer = transfer_buffer.get(),
            .offset = 0,
        };

        const SDL_GPUBufferRegion destination{
            .buffer = &gpu_buffer.get(),
            .offset = 0,
            .size = transfer_info.size
        };

        SDL_UploadToGPUBuffer(copy_pass.value(), &source, &destination, true);

        endCopyPass(copy_pass.value());

        const auto submit_result = SDL_SubmitGPUCommandBuffer(command_buffer_.get());
        if (!submit_result)
        {
            std::println("SDL_SubmitGPUCommandBuffer failed: {}", SDL_GetError());
        }
        return{};
    }

    auto SdlGpuCommandContext::acquireRenderPass(const SDL_GPUColorTargetInfo &color_target) const -> std::expected<SdlGpuRenderPass, EGpuError>
    {
        const auto pass_result = beginRenderPass(color_target);
        if (!pass_result)
        {
            std::println("SDL_BeginRenderPass failed: {}",SDL_GetError());
            return std::unexpected(pass_result.error());
        }
        const auto render_pass = pass_result.value();
        return SdlGpuRenderPass{render_pass};
    }

    auto SdlGpuCommandContext::draw(const SDL_GPUColorTargetInfo& color_target,
                                    const resource::SdlGpuGraphicsPipelineBrPtr pipeline,
                                    const resource::SdlGpuBufferBrPtr gpu_buffer,
                                    const std::uint32_t vertex_count) const -> std::expected<void, EGpuError>
    {
        const auto result = beginRenderPass(color_target);
        if (!result)
        {
            std::println("SDL_BeginRenderPass failed: {}",SDL_GetError());
            return std::unexpected(result.error());
        }
        const auto render_pass = result.value();
        SDL_BindGPUGraphicsPipeline(render_pass, &pipeline.get());

        const SDL_GPUBufferBinding vertex_buffer_binding{
            .buffer = &gpu_buffer.get(),
            .offset = 0
        };

        SDL_BindGPUVertexBuffers(render_pass, 0, &vertex_buffer_binding, 1);

        SDL_DrawGPUPrimitives(render_pass, vertex_count, 1, 0, 0);

        SDL_EndGPURenderPass(render_pass);

        return {};
    }

    auto SdlGpuCommandContext::beginCopyPass() const -> std::expected<SDL_GPUCopyPass*, EGpuError>
    {
        SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(command_buffer_.get());
        if (!copy_pass)
        {
            std::println("SDL_BeginGPUCopyPass failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::GPU_COPY_PASS_BEGIN_FAILED);
        }
        return copy_pass;
    }

    void SdlGpuCommandContext::endCopyPass(SDL_GPUCopyPass* copy_pass)
    {
        SDL_EndGPUCopyPass(copy_pass);
    }

    auto SdlGpuCommandContext::beginRenderPass(const SDL_GPUColorTargetInfo& color_target) const -> std::expected<SDL_GPURenderPass*, EGpuError>
    {
        SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(command_buffer_.get(), &color_target, 1,nullptr);
        if (!render_pass)
        {
            std::println("SDL_BeginGPURenderPass failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::GPU_RENDER_PASS_BEGIN_FAILED);
        }
        return render_pass;
    }

    void SdlGpuCommandContext::endRenderPass(SDL_GPURenderPass* render_pass)
    {
        SDL_EndGPURenderPass(render_pass);
    }
}
