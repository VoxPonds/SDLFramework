#define SDL_MAIN_USE_CALLBACKS  /* use the callbacks instead of main() */
#include "sdl3/SDL_main.h"

import engine.core.application;
import example.world;
import std;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	auto& app = engine::core::Application::instance();

	auto* world = new example::world::GameWorld(
		app.getResourceManager(),
		app.getRenderer()
	);

	*appstate = world;

	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_KEY_DOWN ||
		event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	//engine::core::Application::instance().test();

	auto* world = static_cast<example::world::GameWorld*>(appstate);

	auto resource_result = world->loadResource();
	auto render_result = world->draw();
	engine::core::Application::instance().getRenderer()->renderFrame();

	return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult)
{
	delete static_cast<example::world::GameWorld*>(appstate);
}