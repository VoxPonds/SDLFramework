module;
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"

module engine.render.sdlgpurenderer;

namespace engine::render
{
    SdlGpuRenderer::SdlGpuRenderer(utilities::BorrowedPtr<SdlGpuDevice> device,
        resource::ResourceManager& manager):
        device_wrapper_(device.get()),
        device_(device_wrapper_->device()),
        resource_manager_borrowed_(manager),
        swapchain_texture_(nullptr),
        frame_state_(EFrameState::IDLE)
    {
    }

    auto SdlGpuRenderer::beginFrame() const -> std::expected<void, EGpuError>
    {
        const auto upload_command_buffer = device_wrapper_->acquireCommandBuffer();
        if (!upload_command_buffer)
        {
            std::println("SDL_AcquireGPUCommandBuffer failed: {}",SDL_GetError());
            return std::unexpected(upload_command_buffer.error());
        }
        return {};
    }

    auto SdlGpuRenderer::endFrame() -> std::expected<void, EGpuError>
    {
        return{};
    }

    auto SdlGpuRenderer::execute(const RenderCommand3D &render_command_3d) -> std::expected<void, EGpuError>
    {
        return {};
    }

    auto SdlGpuRenderer::submit(platform::GPUCommandBufferBrPtr command_buffer) -> std::expected<void, EGpuError>
    {
        if (!SDL_SubmitGPUCommandBuffer(&command_buffer.get()))
        {
            std::println("SDL_SubmitGPUCommandBuffer failed: {}", SDL_GetError());
            return std::unexpected(EGpuError::SUBMIT_GPU_COMMAND_BUFFER_FAILED);
        }
        return {};
    }

    auto SdlGpuRenderer::renderTest() -> std::expected<void, EGpuError>
    {
        constexpr SDL_GPUBufferCreateInfo test_buffer_info{
            .usage = SDL_GPU_BUFFERUSAGE_VERTEX,
            .size = sizeof(vertices),
            //.props =
        };

        const auto gpu_buffer = device_wrapper_->createGpuBuffer(test_buffer_info);
        if (!gpu_buffer)
        {
            return std::unexpected(gpu_buffer.error());
        }

        const auto upload_command_buffer = device_wrapper_->acquireCommandBuffer();
        if (!upload_command_buffer)
        {
            return std::unexpected(upload_command_buffer.error());
        }
        command_context_.emplace(utilities::borrow(*device_wrapper_->device()),
            utilities::borrow(*upload_command_buffer.value().get()));

        //submit
        auto upload_result = command_context_->uploadBuffer(
            utilities::BorrowedPtr{gpu_buffer.value().get()}, std::span<const Vertex>{vertices}
        );
        if (!upload_result)
        {
            return std::unexpected(upload_result.error());
        }

         SDL_GPUVertexBufferDescription vertex_buffer_description{
            .slot = 0,
            .pitch = sizeof(Vertex),
            .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
            .instance_step_rate = 0
        };

        SDL_GPUVertexAttribute vertex_attribute{
            .location = 0,
            .buffer_slot = 0,
            .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
            .offset = 0
        };

        SDL_GPUVertexInputState vertex_input_state{
            .vertex_buffer_descriptions = &vertex_buffer_description,
            .num_vertex_buffers = 1,
            .vertex_attributes = &vertex_attribute,
            .num_vertex_attributes = 1
        };

        SDL_GPUTextureFormat swapchain_format = SDL_GetGPUSwapchainTextureFormat(device_.get(), device_wrapper_->window().get());

        SDL_GPUColorTargetDescription color_target_description{
            .format = swapchain_format,
        };

        SDL_GPUGraphicsPipelineTargetInfo target_info{
            .color_target_descriptions = &color_target_description,
            .num_color_targets = 1,
        };
        auto test_vertex_shader = loadShader(
            device_.get(),
            "shaders/triangle.vert.spv",
            SDL_GPU_SHADERSTAGE_VERTEX
        );

        auto test_fragment_shader = loadShader(
            device_.get(),
            "shaders/triangle.frag.spv",
            SDL_GPU_SHADERSTAGE_FRAGMENT
        );
        SDL_GPUGraphicsPipelineCreateInfo test_pipeline_info{
            .vertex_shader = test_vertex_shader,
            .fragment_shader = test_fragment_shader,
            .vertex_input_state = vertex_input_state,
            .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,

            .rasterizer_state{
                .fill_mode = SDL_GPU_FILLMODE_FILL,
                .cull_mode = SDL_GPU_CULLMODE_NONE,
            },

            .multisample_state{
                .sample_count = SDL_GPU_SAMPLECOUNT_1,
            },

            .target_info = target_info
        };
        const auto pipeline = device_wrapper_->createGraphicsPipeline(test_pipeline_info);

        const auto command_buffer = device_wrapper_->acquireCommandBuffer();
        if (!command_buffer)
        {
            return std::unexpected(command_buffer.error());
        }
        command_context_.emplace(utilities::borrow(*device_.get()),
            utilities::borrow(*command_buffer.value().get()));

        Uint32 width = 0;
        Uint32 height = 0;

        if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer->get(), device_wrapper_->window().get(),
            swapchain_texture_.put(), &width, &height))
        {
            std::println("SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",SDL_GetError());
        }

        if (swapchain_texture_)
        {
            constexpr SDL_FColor clear_color{
                .r = 0.0f,
                .g = 1.1f,
                .b = 0.15f,
                .a = 1.0f
            };

            SDL_GPUColorTargetInfo color_target{
                .texture = swapchain_texture_.get(),
                .clear_color = clear_color,
                .load_op = SDL_GPU_LOADOP_CLEAR,
                .store_op = SDL_GPU_STOREOP_STORE
            };
            auto draw_result =
                command_context_->draw(color_target,
                    utilities::borrow(*pipeline->get()),
                    utilities::borrow(*gpu_buffer->get()), 3
                );
            if (!draw_result)
            {
                return std::unexpected(draw_result.error());
            }
        }
        const auto submit_result = submit(utilities::borrow(*command_buffer->get()));
        if (!submit_result)
        {
            return std::unexpected(submit_result.error());
        }
        return{};
    }

    auto SdlGpuRenderer::render(const FrameData &data) -> std::expected<void, ERendererError>
    {
        return {};
    }
}
