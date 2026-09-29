module;

export module engine.core.appconfig;
import std;

export namespace engine::core
{
    struct WindowConfig
    {
        int width{800};
        int height{600};
        std::string_view title{"Default Title"};
        std::uint64_t flags{32};
    };

    struct AppConfig
    {
        WindowConfig window_config_;
    };

    inline constexpr AppConfig froth_default_app_config;
}
