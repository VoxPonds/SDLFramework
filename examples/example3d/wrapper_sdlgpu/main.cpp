#define FROTH_MANUAL_FRAMEWORK_MODE
#include <froth/entry.h>

import engine.core.runtime;
import example3d.wrappersdlgpu;
import engine.render.rendertypes;

int main(int argc, char** argv)
{
    auto& runtime = engine::core::Runtime<WrapperSdlGpuTest>::instance(engine::render::ERenderBackend::SDL_GPU);
    runtime.init();

    while (runtime.isRunning())
    {
        runtime.beginFrame();

        runtime.processEvents();

        runtime.iterate();

        runtime.endFrame();
    }

    runtime.quit();
    return 0;
}
