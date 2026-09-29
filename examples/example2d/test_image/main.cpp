#define FROTH_MANUAL_FRAMEWORK_MODE
//#define FROTH_DELEGATE_FRAMEWORK_MODE

#include <froth/entry.h>
#ifdef FROTH_MANUAL_FRAMEWORK_MODE
import engine.core.runtime;
import example2d.imgae;
import engine.render.rendertypes;

int main(int argc, char* argv[])
{
	auto& runtime = engine::core::Runtime<GameApp>::instance(engine::render::ERenderBackend::SDL_RENDERER);
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
#endif

#ifdef FROTH_DELEGATE_FRAMEWORK_MODE
import example2d.imgae;
FROTH_RUN_APP(GameApp)
#endif







