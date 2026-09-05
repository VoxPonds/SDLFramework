module;

export module engine.render.rendertypes;
import std;

export namespace engine::render
{
    enum class ERenderBackend : std::uint8_t
    {
        SDL_RENDERER,
        SDL_GPU,
        VULKAN,
        BGFX,
        WEB_GPU
    };

    enum class ERenderPass : std::uint8_t
    {
        OPAQUE_3D,
        TRANSPARENT_3D,
        SPRITE_WORLD,
        SPRITE_SCREEN,
        DEBUG
    };

    struct RenderCapabilities
    {
        bool supports_3d{};
        bool supports_compute{};
        bool supports_msaa{};
        bool supports_bindless{};
        bool supports_texture_compression{};

        std::uint32_t max_texture_size{};
        std::uint32_t max_frames_in_flight{};
    };

    struct RenderSortKey
    {
        ERenderPass pass{};
        std::uint32_t layer{};
        std::uint32_t pipeline{};
        std::uint32_t material{};
        std::uint32_t mesh{};
        float depth{};
    };
}