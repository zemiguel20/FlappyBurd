#pragma once

#include <SDL.h>

struct GameSettings
{
	unsigned int screenWidth;
	unsigned int screenHeight;
};

/* @brief Game represented as an object. This class takes care of initializing the game
* and running the main loop.
* Only one instance should be created.
*/
class Game
{
private:
	/* Pointer to the game window object */
	SDL_Window* m_window;

	/* Pointer to renderer object */
	SDL_Renderer* m_renderer;

	/* Tells if the game loop should be running. */
	bool m_running;

	GameSettings m_settings;

public:
	/* Initializes core systems. Only one instance shouls be created.
	*
	* @param set - game settings.
	*/
	Game(GameSettings set);
	~Game();

	/* @brief Runs the game loop while 'running' is set to true.
	*/
	void Run();

private:
	void ProcessEventQueue();
};

