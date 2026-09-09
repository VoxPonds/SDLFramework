module;
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_log.h"

export module engine.render.sdlgpudevice;

import engine.render.rendertypes;
import engine.platform.sdlptr;
import std;

export namespace engine::render
{
    class SdlGpuDevice
    {
        private:
            platform::SdlGpuDevicePtr sdl_gpu;
            RenderCapabilities capabilities_;

        public:
            SdlGpuDevice(SDL_Window& window_borrowed);
            ~SdlGpuDevice() = default;

            platform::SdlGpuDeviceObPtr getSdlGpu() const;

            static RenderCapabilities getCapabilities();
    };

    SdlGpuDevice::SdlGpuDevice(SDL_Window& window_borrowed):
        sdl_gpu(
            SDL_CreateGPUDevice(
                SDL_GPU_SHADERFORMAT_SPIRV |
                SDL_GPU_SHADERFORMAT_DXIL  |
                SDL_GPU_SHADERFORMAT_MSL,
                true,
                nullptr
            )
        )
    {
        if (!sdl_gpu) {
            const auto error = std::string("Failed to create SDL renderer: ") + SDL_GetError();
            throw std::runtime_error(error);
        }
        if (!SDL_ClaimWindowForGPUDevice(sdl_gpu.get(), &window_borrowed)) {
            const auto error = std::string("SDL_ClaimWindowForGPUDevice failed: %s") + SDL_GetError();
            throw std::runtime_error(error);
        }
        SDL_Log("GPU driver: %s", SDL_GetGPUDeviceDriver(sdl_gpu.get()));
    }

    platform::SdlGpuDeviceObPtr SdlGpuDevice::getSdlGpu() const
    {
        return sdl_gpu;
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
