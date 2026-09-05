#define FROTH_MANUAL_FRAMEWORK_MODE
//#define FROTH_DELEGATE_FRAMEWORK_MODE

#include <froth/entry.h>
#ifdef FROTH_MANUAL_FRAMEWORK_MODE
import engine.core.runtime;
import example2d;

int main(int argc, char* argv[])
{
	auto& runtime = engine::core::Runtime<GameApp>::instance();
	runtime.init();

	while (runtime.isRunning())
	{
		runtime.beginFrame();

		runtime.processEvent();

		runtime.iterate();

		runtime.endFrame();
	}

	runtime.quit();
	return 0;
}
#endif

#ifdef FROTH_DELEGATE_FRAMEWORK_MODE
import example2d;
FROTH_RUN_APP(GameApp)
#endif







