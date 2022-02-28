#pragma once

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
	/* Pointer to the game window object */
	void* window;

	/* Tells if the game loop should be running. */
	bool running;

	GameSettings settings;

};

