#define FROTH_MANUAL_FRAMEWORK_MODE
#include <froth/entry.h>

import std;

static constexpr std::vector<Uint8> readBinaryFile(const std::filesystem::path& path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::println("Failed to open file: {}", path.string());
    }
    const auto size = file.tellg();
    std::vector<Uint8> data(size);

    file.seekg(0);
    file.read(reinterpret_cast<char*>(data.data()), size);
    if (!file)
    {
        std::println("Failed to create shader '{}': {}", path.string(), SDL_GetError());
    }
    return data;
}

static constexpr SDL_GPUShader* loadShader(SDL_GPUDevice* device, const std::filesystem::path& path, const SDL_GPUShaderStage stage)
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

struct Vertex
{
    float x;
    float y;
    float z;
};

int main(int argc, char* argv[])
{
    /*for (int i = 0; i < SDL_GetNumGPUDrivers(); i++) {
        std::cout << SDL_GetGPUDriver(i) << std::endl;
    }*/
    std::println("Working directory: {}",std::filesystem::current_path().string());

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::println("SDL_Init failed: {}", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL GPU",
        1280,
        720,
        SDL_WINDOW_RESIZABLE
    );
    if (!window)
    {
        std::println("SDL_CreateWindow failed: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GPUDevice* device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV
        /*|SDL_GPU_SHADERFORMAT_DXIL
        |SDL_GPU_SHADERFORMAT_MSL*/
        ,
        true,
        nullptr
    );
    std::println("GPU driver: {}", SDL_GetGPUDeviceDriver(device)
);
    if (!device)
    {
        std::println("SDL_CreateGPUDevice failed: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!SDL_ClaimWindowForGPUDevice(device, window))
    {
        std::println("SDL_ClaimWindowForGPUDevice failed: {}",SDL_GetError());
        SDL_DestroyGPUDevice(device);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    constexpr std::array vertices{
        Vertex{  .x = 0.0f, .y = -0.5f, .z = 0.0f },
        Vertex{  .x = 0.5f,  .y = 0.5f, .z = 0.0f },
        Vertex{ .x = -0.5f,  .y = 0.5f, .z = 0.0f }
    };

    auto vertex_shader = loadShader(
        device,
        "shaders/triangle.vert.spv",
        SDL_GPU_SHADERSTAGE_VERTEX
    );

    auto fragment_shader = loadShader(
        device,
        "shaders/triangle.frag.spv",
        SDL_GPU_SHADERSTAGE_FRAGMENT
    );

    SDL_GPUBufferCreateInfo buffer_info{
        .usage = SDL_GPU_BUFFERUSAGE_VERTEX,
        .size = sizeof(vertices),
        //.props =
    };

    SDL_GPUBuffer* gpu_buffer = SDL_CreateGPUBuffer(device, &buffer_info);
    if (!gpu_buffer)
    {
        std::println("SDL_CreateGPUBuffer failed: {}",SDL_GetError());
        return 1;
    }

    SDL_GPUTransferBufferCreateInfo transfer_info{
        .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        .size = sizeof(vertices),
        //.props =
    };

    SDL_GPUTransferBuffer* transfer_buffer = SDL_CreateGPUTransferBuffer(device, &transfer_info);
    if (!transfer_buffer)
    {
        std::println("SDL_CreateGPUTransferBuffer failed: {}",SDL_GetError());
        SDL_ReleaseGPUBuffer(device, gpu_buffer);
        return 1;
    }

    void* mapped = SDL_MapGPUTransferBuffer(device, transfer_buffer,true);
    if (!mapped)
    {
        std::println("SDL_MapGPUTransferBuffer failed: {}",SDL_GetError());
        SDL_ReleaseGPUTransferBuffer(device, transfer_buffer);
        SDL_ReleaseGPUBuffer(device, gpu_buffer);
        return 1;
    }

    std::memcpy(mapped, vertices.data(), sizeof(vertices));

    SDL_UnmapGPUTransferBuffer(device, transfer_buffer);

    SDL_GPUCommandBuffer* upload_command_buffer = SDL_AcquireGPUCommandBuffer(device);
    if (!upload_command_buffer)
    {
        std::println("SDL_AcquireGPUCommandBuffer failed: {}",SDL_GetError());
        return 1;
    }

    SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(upload_command_buffer);
    if (!copy_pass)
    {
        std::println("SDL_BeginGPUCopyPass failed: {}",SDL_GetError());
        return 1;
    }

    SDL_GPUTransferBufferLocation source{
        .transfer_buffer = transfer_buffer,
        .offset = 0,
    };

    SDL_GPUBufferRegion destination{
        .buffer = gpu_buffer,
        .offset = 0,
        .size = transfer_info.size
    };

    SDL_UploadToGPUBuffer(copy_pass, &source, &destination, true);

    SDL_EndGPUCopyPass(copy_pass);

    SDL_SubmitGPUCommandBuffer(upload_command_buffer);

//pipeline
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

    SDL_GPUTextureFormat swapchain_format = SDL_GetGPUSwapchainTextureFormat(device, window);

    SDL_GPUColorTargetDescription color_target_description{
        .format = swapchain_format,
    };

    SDL_GPUGraphicsPipelineTargetInfo target_info{
        .color_target_descriptions = &color_target_description,
        .num_color_targets = 1,
    };

    SDL_GPUGraphicsPipelineCreateInfo pipeline_info{
        .vertex_shader = vertex_shader,
        .fragment_shader = fragment_shader,
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

    SDL_GPUGraphicsPipeline* pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipeline_info);
    if (!pipeline)
    {
        std::println("SDL_CreateGPUGraphicsPipeline failed: {}",SDL_GetError());
        return 1;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(device);
        if (!command_buffer)
        {
            std::println("SDL_AcquireGPUCommandBuffer failed: {}",SDL_GetError());
            break;
        }

        SDL_GPUTexture* swapchain_texture = nullptr;

        Uint32 width = 0;
        Uint32 height = 0;

        if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, &width, &height))
        {
            std::println("SDL_WaitAndAcquireGPUSwapchainTexture failed: {}",SDL_GetError());
            break;
        }

        if (swapchain_texture)
        {
            constexpr SDL_FColor clear_color{
                .r = 0.0f,
                .g = 0.1f,
                .b = 0.15f,
                .a = 1.0f
            };

            SDL_GPUColorTargetInfo color_target{
                .texture = swapchain_texture,
                .clear_color = clear_color,
                .load_op = SDL_GPU_LOADOP_CLEAR,
                .store_op = SDL_GPU_STOREOP_STORE
            };

            SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(command_buffer, &color_target, 1,nullptr);

            SDL_BindGPUGraphicsPipeline(render_pass,pipeline);

            SDL_GPUBufferBinding vertex_buffer_binding{
                .buffer = gpu_buffer,
                .offset = 0
            };

            SDL_BindGPUVertexBuffers(render_pass, 0, &vertex_buffer_binding, 1);

            SDL_DrawGPUPrimitives(render_pass, 3, 1, 0, 0);

            SDL_EndGPURenderPass(render_pass);
        }

        if (!SDL_SubmitGPUCommandBuffer(command_buffer))
        {
            std::println("SDL_SubmitGPUCommandBuffer failed: {}", SDL_GetError());
            break;
        }
    }

    SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
    SDL_ReleaseGPUShader(device, vertex_shader);
    SDL_ReleaseGPUShader(device, fragment_shader);
    SDL_ReleaseGPUBuffer(device, gpu_buffer);
    SDL_ReleaseGPUTransferBuffer(device, transfer_buffer);
    SDL_ReleaseWindowFromGPUDevice(device, window);
    SDL_DestroyGPUDevice(device);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
