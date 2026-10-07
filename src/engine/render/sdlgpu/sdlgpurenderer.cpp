module;
#include "SDL3/SDL_gpu.h"

module engine.render.sdlgpurenderer;

import engine.resource.resourcetraits;
import engine.render.mesh;

namespace engine::render
{
    SdlGpuRenderer::SdlGpuRenderer(const utilities::BorrowedPtr<SdlGpuDevice> device,
        resource::ResourceManager& manager):
        m_device_wrapper_(device.get()),
        m_device_(m_device_wrapper_->device()),
        m_resource_manager_borrowed_(manager),
        m_swapchain_texture_(nullptr),
        m_gpu_buffer_{},
        m_frame_state_(EFrameState::IDLE)
    {
        if (const auto init_result = initialize(); !init_result)
        {
            throw std::runtime_error{
                std::format(
                    "Failed to initialize SdlGpuRenderer: {}",
                    std::to_underlying(init_result.error())
                )
            };
        }
    }

    auto SdlGpuRenderer::render(const FrameData &data) -> std::expected<void, ERendererError>
    {
        //std::println("3D COMMAND AMOUNTS: {}", data.command3ds_.commands().size());
        auto commands = data.command3ds_.commands();
        auto& camera = data.camera;
        return beginFrame().transform_error(toRendererError)
            .and_then([this]
            {
                return clear().transform_error(toRendererError);
            })
            .and_then([&]
            {
                return execute(camera, commands).transform_error(toRendererError);
            })
            .and_then([this]
            {
                return endFrame().transform_error(toRendererError);
            });
    }

    auto SdlGpuRenderer::initialize() -> std::expected<void, EGpuError>
    {
         constexpr SDL_GPUBufferCreateInfo buffer_info{
            .usage {SDL_GPU_BUFFERUSAGE_VERTEX},
            .size  {1024},
            //.props =
        };

        auto gpu_buffer_result = m_device_wrapper_->createGpuBuffer(buffer_info);
        if (!gpu_buffer_result)
        {
            return std::unexpected(gpu_buffer_result.error());
        }
        m_gpu_buffer_ = std::move(*gpu_buffer_result);

        SDL_GPUVertexBufferDescription vertex_buffer_description{
            .slot = 0,
            .pitch = sizeof(VertexData),
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

        SDL_GPUTextureFormat swapchain_format = SDL_GetGPUSwapchainTextureFormat(m_device_.get(), m_device_wrapper_->window().get());

        SDL_GPUColorTargetDescription color_target_description{
            .format = swapchain_format,
        };

        SDL_GPUGraphicsPipelineTargetInfo target_info{
            .color_target_descriptions = &color_target_description,
            .num_color_targets = 1,
        };
        auto test_vertex_shader = loadShader(
            m_device_.get(),
            "shaders/triangle.vert.spv",
            SDL_GPU_SHADERSTAGE_VERTEX
        );
        auto test_fragment_shader = loadShader(
            m_device_.get(),
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

        auto pipeline_result = m_device_wrapper_->createGraphicsPipeline(test_pipeline_info);
        if (!pipeline_result)
        {
            return std::unexpected(pipeline_result.error());
        }
        m_pipeline_ = std::move(*pipeline_result);
        return{};
    }

    auto SdlGpuRenderer::beginFrame() -> std::expected<void, EGpuError>
    {
        if (m_frame_state_ != EFrameState::IDLE)
        {
            return std::unexpected(EGpuError::INVALID_FRAME_STATE);
        }

        m_frame_state_ = EFrameState::BEGUN;

        return {};
    }

    auto SdlGpuRenderer::clear() -> std::expected<void, EGpuError>
    {
        return {};
    }

    auto SdlGpuRenderer::execute(const Camera& camera, const std::span<const RenderCommand3D> command_3d_list) -> std::expected<void, EGpuError>
    {
        if (m_frame_state_ != EFrameState::BEGUN)
        {
            return std::unexpected(EGpuError::INVALID_FRAME_STATE);
        }

        const auto upload_command_buffer = m_device_wrapper_->acquireCommandBuffer();
        if (!upload_command_buffer)
        {
            return std::unexpected(upload_command_buffer.error());
        }
        m_command_context_.emplace(util::borrow(*m_device_wrapper_->device()),
            util::borrow(*upload_command_buffer->get()));

        for (const auto& command_3d : command_3d_list)
        {
            const auto result = std::visit(
                [&]<typename T>(const T& command) -> std::expected<void, EGpuError>
                {
                    using DT = std::remove_cvref_t<T>;
                    if constexpr (std::same_as<DT, MeshRenderCommand>)
                    {
                        auto upload_result = m_command_context_->uploadBuffer(
                            util::BorrowedPtr{m_gpu_buffer_.get()},
                            command.mesh.vertices
                        );
                        if (!upload_result)
                        {
                            return std::unexpected(upload_result.error());
                        }
                    }
                    return {};
                },
                command_3d
            );
            if (!result)
            {
                return std::unexpected(result.error());
            }
        }

        const auto render_command_buffer = m_device_wrapper_->acquireCommandBuffer();
        if (!render_command_buffer)
        {
            std::println("SDL_AcquireGPUCommandBuffer failed: {}", SDL_GetError());
            return std::unexpected(render_command_buffer.error());
        }

        std::uint32_t width{};
        std::uint32_t height{};

        if (!SDL_WaitAndAcquireGPUSwapchainTexture(render_command_buffer->get(), m_device_wrapper_->window().get(),
            m_swapchain_texture_.put(), &width, &height))
        {
            std::println("SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::ACQUIRE_SWAPCHAIN_TEXTURE_FAILED);
        }

        m_command_buffer_ = std::move(*render_command_buffer);

        m_frame_width_ = width;
        m_frame_height_ = height;

        m_command_context_.emplace(
            util::borrow(*m_device_.get()),
            util::borrow(*m_command_buffer_.get())
        );

        if (!m_swapchain_texture_)
        {
            return std::unexpected(EGpuError::ACQUIRE_SWAPCHAIN_TEXTURE_FAILED);
        }

        //render_pass
        {
            constexpr SDL_FColor clear_color{
                .r = 0.0f,
                .g = 1.0f,
                .b = 0.15f,
                .a = 1.0f
            };

            const SDL_GPUColorTargetInfo color_target{
                .texture = m_swapchain_texture_.get(),
                .clear_color = clear_color,
                .load_op = SDL_GPU_LOADOP_CLEAR,
                .store_op = SDL_GPU_STOREOP_STORE
            };

            auto render_pass = m_command_context_->acquireRenderPass(color_target);
            if (!render_pass)
            {
                return std::unexpected(render_pass.error());
            }

            for (const auto& command_3d : command_3d_list)
            {
                std::visit(
                    [&]<typename T>(const T& command)
                    {
                        using DT = std::remove_cvref_t<T>;
                        if constexpr (std::same_as<DT, MeshRenderCommand>)
                        {
                            render_pass->bindPipeline(util::borrow(*m_pipeline_));
                            render_pass->bindVertexBuffer(util::borrow(*m_gpu_buffer_));
                            render_pass->draw(static_cast<std::uint32_t>(command.mesh.vertices.size()));
                        }
                    },
                    command_3d
                );
            }
        }

        return {};
    }

    auto SdlGpuRenderer::endFrame() -> std::expected<void, EGpuError>
    {
        if (m_frame_state_ != EFrameState::BEGUN)
        {
            return std::unexpected(EGpuError::INVALID_FRAME_STATE);
        }

        if (const auto result = submit(util::borrow(*m_command_buffer_)); !result)
        {
            return std::unexpected(result.error());
        }

        m_command_context_.reset();
        m_command_buffer_ = {};
        m_swapchain_texture_ = {};
        m_frame_state_ = EFrameState::IDLE;

        return {};
    }

    auto SdlGpuRenderer::submit(platform::SdlGpuCommandBufferBrPtr command_buffer) -> std::expected<void, EGpuError>
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

        const auto gpu_buffer = m_device_wrapper_->createGpuBuffer(test_buffer_info);
        if (!gpu_buffer)
        {
            return std::unexpected(gpu_buffer.error());
        }

        const auto upload_command_buffer = m_device_wrapper_->acquireCommandBuffer();
        if (!upload_command_buffer)
        {
            return std::unexpected(upload_command_buffer.error());
        }
        m_command_context_.emplace(utilities::borrow(*m_device_wrapper_->device()),
            utilities::borrow(*upload_command_buffer.value().get()));

        //submit
        auto upload_result = m_command_context_->uploadBuffer(
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

        SDL_GPUTextureFormat swapchain_format = SDL_GetGPUSwapchainTextureFormat(m_device_.get(), m_device_wrapper_->window().get());

        SDL_GPUColorTargetDescription color_target_description{
            .format = swapchain_format,
        };

        SDL_GPUGraphicsPipelineTargetInfo target_info{
            .color_target_descriptions = &color_target_description,
            .num_color_targets = 1,
        };
        m_vertex_shader_ = resource::SdlGpuShaderPtr{
            loadShader(
                m_device_.get(),
                "shaders/triangle.vert.spv",
                SDL_GPU_SHADERSTAGE_VERTEX
            )
        };

        m_fragment_shader_ = resource::SdlGpuShaderPtr{
            loadShader(
                m_device_.get(),
                "shaders/triangle.frag.spv",
                SDL_GPU_SHADERSTAGE_FRAGMENT
            )
        };
        SDL_GPUGraphicsPipelineCreateInfo test_pipeline_info{
            .vertex_shader = m_vertex_shader_.get(),
            .fragment_shader = m_fragment_shader_.get(),
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
        const auto pipeline = m_device_wrapper_->createGraphicsPipeline(test_pipeline_info);

        const auto command_buffer = m_device_wrapper_->acquireCommandBuffer();
        if (!command_buffer)
        {
            return std::unexpected(command_buffer.error());
        }
        m_command_context_.emplace(utilities::borrow(*m_device_.get()),
            utilities::borrow(*command_buffer.value().get()));

        Uint32 width = 0;
        Uint32 height = 0;

        if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer->get(), m_device_wrapper_->window().get(),
            m_swapchain_texture_.put(), &width, &height))
        {
            std::println("SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",SDL_GetError());
        }

        if (m_swapchain_texture_)
        {
            constexpr SDL_FColor clear_color{
                .r = 0.0f,
                .g = 1.1f,
                .b = 0.15f,
                .a = 1.0f
            };

            SDL_GPUColorTargetInfo color_target{
                .texture = m_swapchain_texture_.get(),
                .clear_color = clear_color,
                .load_op = SDL_GPU_LOADOP_CLEAR,
                .store_op = SDL_GPU_STOREOP_STORE
            };
            auto draw_result =
                m_command_context_->draw(color_target,
                    utilities::borrow(*pipeline->get()),
                    utilities::borrow(*gpu_buffer->get()), 3
                );
            if (!draw_result)
            {
                return std::unexpected(draw_result.error());
            }
        }
        if (const auto submit_result = submit(utilities::borrow(*command_buffer->get())); !submit_result)
        {
            return std::unexpected(submit_result.error());
        }
        return{};
    }
}
