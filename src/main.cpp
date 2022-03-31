#include "Game.h"
#include <iostream>

int main()
{
	try
	{
		Game game;
		game.Run();
	}
	catch (const char* errMsg)
	{
		std::cerr << errMsg << std::endl;
		return -1;
	}

	return 0;
}