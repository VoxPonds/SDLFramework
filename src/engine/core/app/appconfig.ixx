module;

export module engine.core.appconfig;

import std;


export namespace engine::core
{
    struct WindowConfig
    {
        std::size_t width{800};
        std::size_t height{600};
        std::string_view title{"Default Title"};
        std::uint64_t flags{32};
    };

    struct InputConfig
    {

    };


    struct AppConfig
    {
        WindowConfig window_config_;
        InputConfig input_config_;
    };


    inline constexpr AppConfig froth_default_app_config;
}
