module;
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_log.h"

module engine.render.sdlgpudevice;
import std;

namespace engine::render
{
    std::vector<std::uint8_t> readBinaryFile(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw std::runtime_error(
                std::format("Failed to open file: {}", path.string())
            );
        }
        const auto size = file.tellg();
        std::vector<std::uint8_t> data(size);

        file.seekg(0);
        file.read(reinterpret_cast<char*>(data.data()), size);
        if (!file)
        {
            throw std::runtime_error(
                std::format("Failed to create shader '{}': {}", path.string(), SDL_GetError())
            );
        }
        return data;
    }
    SDL_GPUShader* loadShader(SDL_GPUDevice* device, const std::filesystem::path& path, const SDL_GPUShaderStage stage)
    {
        const auto code = readBinaryFile(path);

        const SDL_GPUShaderCreateInfo info{
            .code_size = code.size(),
            .code = code.data(),
            .entrypoint = "main",
            .format = SDL_GPU_SHADERFORMAT_SPIRV,
            .stage = stage,
            .num_samplers = 0,
            .num_storage_textures = 0,
            .num_storage_buffers = 0,
            .num_uniform_buffers = 0
        };

        SDL_GPUShader* shader = SDL_CreateGPUShader(device, &info);

        if (!shader)
        {
            throw std::runtime_error(
                std::format("Failed to create shader '{}': {}", path.string(), SDL_GetError())
            );
        }
        return shader;
    }

    SdlGpuDevice::SdlGpuDevice(SDL_Window& window):
        sdl_gpu_device(
            SDL_CreateGPUDevice(
                SDL_GPU_SHADERFORMAT_SPIRV,
                /*|SDL_GPU_SHADERFORMAT_DXIL
                |SDL_GPU_SHADERFORMAT_MSL,*/
                true,
                nullptr
            )
        ), window_borrowed(window)
    {
        if (!sdl_gpu_device) {
            const auto error = std::format("Failed to create SDL renderer: {}", SDL_GetError());
            throw std::runtime_error(error);
        }
        if (!SDL_ClaimWindowForGPUDevice(sdl_gpu_device.get(), window_borrowed.get())) {
            const auto error = std::format("SDL_ClaimWindowForGPUDevice failed: {}", SDL_GetError());
            throw std::runtime_error(error);
        }
        SDL_Log("GPU driver: %s", SDL_GetGPUDeviceDriver(sdl_gpu_device.get()));
    }

    SdlGpuDevice::~SdlGpuDevice()
    {
        SDL_ReleaseWindowFromGPUDevice(sdl_gpu_device.get(), window_borrowed.get());
    }

    platform::SdlGpuDeviceObPtr SdlGpuDevice::device() const
    {
        return platform::SdlGpuDeviceObPtr(sdl_gpu_device);
    }

    platform::WindowObPtr SdlGpuDevice::window() const
    {
        return  window_borrowed;
    }

    auto SdlGpuDevice::createShader(const std::filesystem::path& path,
                                    const SDL_GPUShaderStage stage) const -> std::expected<resource::SdlGpuShaderPtr, EGpuError>
    {
        return
        resource::SdlGpuShaderPtr{
            loadShader(sdl_gpu_device.get(), path, stage),
            resource::ResourceTraits<SDL_GPUShader>::Deleter{ sdl_gpu_device.get() }
        };
    }

    auto SdlGpuDevice::createGpuBuffer(const SDL_GPUBufferCreateInfo& buffer_info) const -> std::expected<resource::SdlGpuBufferPtr, EGpuError>
    {
        const auto gpu_buffer = SDL_CreateGPUBuffer(sdl_gpu_device.get(), &buffer_info);
        if (!gpu_buffer)
        {
            std::println("SDL_CreateGPUBuffer failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::BUFFER_CREATION_FAILED);
        }

        return
        resource::SdlGpuBufferPtr{
            gpu_buffer,
            resource::ResourceTraits<SDL_GPUBuffer>::Deleter{ sdl_gpu_device.get() }
        };
    }

    auto SdlGpuDevice::acquireCommandBuffer() const -> std::expected<platform::GPUCommandBufferObPtr, EGpuError>
    {
        const auto upload_command_buffer = SDL_AcquireGPUCommandBuffer(sdl_gpu_device.get());
        if (!upload_command_buffer)
        {
            std::println("SDL_AcquireGPUCommandBuffer failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::COMMAND_RECORDING_FAILED);
        }
        return std::expected<platform::GPUCommandBufferObPtr, EGpuError>(upload_command_buffer);
    }

    auto SdlGpuDevice::createGraphicsPipeline(const SDL_GPUGraphicsPipelineCreateInfo& info)
        const -> std::expected<resource::SdlGpuGraphicsPipelinePtr, EGpuError>
    {
        /*SDL_GPUVertexBufferDescription vertex_buffer_description{
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

        SDL_GPUTextureFormat swapchain_format = SDL_GetGPUSwapchainTextureFormat(sdl_gpu_device.get(), window_borrowed.get());

        SDL_GPUColorTargetDescription color_target_description{
            .format = swapchain_format,
        };

        SDL_GPUGraphicsPipelineTargetInfo target_info{
            .color_target_descriptions = &color_target_description,
            .num_color_targets = 1,
        };
        auto test_vertex_shader = loadShader(
            sdl_gpu_device.get(),
            "shaders/triangle.vert.spv",
            SDL_GPU_SHADERSTAGE_VERTEX
        );

        auto test_fragment_shader = loadShader(
            sdl_gpu_device.get(),
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
        };*/
        const auto pipeline = SDL_CreateGPUGraphicsPipeline(sdl_gpu_device.get(), &info);
        if (!pipeline)
        {
            std::println("SDL_CreateGPUGraphicsPipeline failed: {}",SDL_GetError());
            return std::unexpected(EGpuError::GRAPHICS_PIPELINE_CREATION_FAILED);
        }
        return
        resource::SdlGpuGraphicsPipelinePtr{
            pipeline,
            resource::ResourceTraits<SDL_GPUGraphicsPipeline>::Deleter{sdl_gpu_device.get()},
        };
    }

    RenderCapabilities SdlGpuDevice::getCapabilities()
    {
        return RenderCapabilities{
            .supports_3d = true,
            .supports_compute = true,
            .supports_msaa = true,
            .supports_bindless = true,
            .supports_texture_compression = false,
        };
    }
}
