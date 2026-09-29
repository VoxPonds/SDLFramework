#ifndef FROTH_FRAMEWORK_ENTRY_H
#define FROTH_FRAMEWORK_ENTRY_H
    #if defined(FROTH_MANUAL_FRAMEWORK_MODE) && defined(FROTH_DELEGATE_FRAMEWORK_MODE)
        #error "FROTH_MANUAL_FRAMEWORK_MODE and FROTH_DELEGATE_FRAMEWORK_MODE cannot be defined at the same time."
    #endif
    #ifdef FROTH_MANUAL_FRAMEWORK_MODE
        #include <SDL3/SDL_main.h>
        #include <SDL3/SDL.h>
    #endif
    #ifdef FROTH_DELEGATE_FRAMEWORK_MODE
        #define SDL_MAIN_USE_CALLBACKS
        #include <SDL3/SDL_main.h>
    #endif
#endif

#ifdef FROTH_DELEGATE_FRAMEWORK_MODE
    import engine.core.runtime;
    import engine.render.rendertypes;

    #define FROTH_RUN_APP(AppType)\
        inline auto& runtime = engine::core::Runtime<AppType>::instance(\
            engine::render::ERenderBackend::SDL_RENDERER,\
            AppType::appConfig()\
        );\
        inline SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])\
        {\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::init, runtime);\
            return SDL_APP_CONTINUE;\
        }\
        inline SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)\
        {\
            if (auto framework_event = engine::platform::translateSDLEvent(*event))\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::processEvent, runtime, framework_event.value());\
            return std::invoke(&engine::core::Runtime<AppType>::isRunning, runtime) ? SDL_APP_CONTINUE : SDL_APP_SUCCESS; \
        }\
        inline SDL_AppResult SDL_AppIterate(void* appstate)\
        {\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::beginFrame, runtime);\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::iterate, runtime);\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::endFrame, runtime);\
            return SDL_APP_CONTINUE;\
        }\
        inline void SDL_AppQuit(void* appstate, SDL_AppResult result)\
        {\
            std::invoke_r<void>(&engine::core::Runtime<AppType>::quit, runtime);\
        }

#endif

