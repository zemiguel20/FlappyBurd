#include "Game.h"

int main()
{
	int code = -1;

	if (Game::Init())
	{
		code = 0;
		Game::Run();
	}

	Game::Close();

	return code;
}