#pragma once

/* @brief Game represented as an object. This class takes care of initializing the game
* and running the main loop.
* Only one instance should be created.
*/
class Game
{
public:
	Game();
	~Game();

	void Run();
};

