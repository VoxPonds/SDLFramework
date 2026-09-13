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
    /*#ifndef FROTH_APP
        #error "FROTH_APP must be defined before including <froth/entry.h>"
    #endif
        inline auto& runtime = engine::core::Runtime<FROTH_APP>::instance();
        /* This function runs once at startup. #1#
        inline SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
        {
            runtime.init();
            return SDL_APP_CONTINUE;
        }

        /* This function runs when a new event (mouse input, keypresses, etc) occurs. #1#
        inline SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
        {
            runtime.processEvent(event);
            if (runtime.isRunning()) return SDL_APP_CONTINUE;
            return SDL_APP_SUCCESS;
        }

        /* This function runs once per frame, and is the heart of the program. #1#
        inline SDL_AppResult SDL_AppIterate(void* appstate)
        {
            runtime.beginFrame();
            runtime.iterate();
            runtime.endFrame();
            return SDL_APP_CONTINUE;
        }

        /* This function runs once at shutdown. #1#
        inline void SDL_AppQuit(void* appstate, SDL_AppResult)
        {
            runtime.quit();
        }*/

    #define FROTH_RUN_APP(AppType)\
        inline auto& runtime = engine::core::Runtime<AppType>::instance(engine::render::ERenderBackend::SDL_RENDERER);\
        inline SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])\
        {\
            runtime.init();\
            return SDL_APP_CONTINUE;\
        }\
        inline SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)\
        {\
            runtime.processEvent(event);\
            return runtime.isRunning() ? SDL_APP_CONTINUE : SDL_APP_SUCCESS; \
        }\
        inline SDL_AppResult SDL_AppIterate(void* appstate)\
        {\
            runtime.beginFrame();\
            runtime.iterate();\
            runtime.endFrame();\
            return SDL_APP_CONTINUE;\
        }\
        inline void SDL_AppQuit(void* appstate, SDL_AppResult result)\
        {\
            runtime.quit();\
        }

#endif

