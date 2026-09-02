#define SDL_MAIN_USE_CALLBACKS  /* use the callbacks instead of main() */
#include "sdl3/SDL_main.h"

import engine.core.runtime;
import example.world;
import std;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	auto& runtime = engine::core::Runtime<example::world::GameApp>::instance();
	runtime.begin();

	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	//engine::core::Runtime<example::world::GameApp>::instance().processEvent(event);
	//if (event->type == SDL_EVENT_KEY_DOWN ||
	//	event->type == SDL_EVENT_QUIT)
	//{
	//	return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	//}
	return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	engine::core::Runtime<example::world::GameApp>::instance().iterate();

	return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult)
{
	engine::core::Runtime<example::world::GameApp>::instance().quit();
}