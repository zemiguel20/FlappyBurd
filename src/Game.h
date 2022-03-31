#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Window.h"

/* @brief Game represented as an object. This class takes care of initializing the game
* and running the main loop.
* Only one instance should be created.
*/
class Game
{
private:

	Window m_window;

	/* Pointer to renderer object */
	SDL_Renderer* m_renderer;

	/* Tells if the game loop should be running. */
	bool m_running;

public:
	/* Initializes core systems. Only one instance shouls be created.
	*
	* @param set - game settings.
	*/
	Game();
	~Game();

	/* @brief Runs the game loop while 'running' is set to true.
	*/
	void Run();

private:
	void ProcessEventQueue();
};

