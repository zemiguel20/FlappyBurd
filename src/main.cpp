#include "Game.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720


int main()
{
	GameSettings settings;
	settings.screenWidth = SCREEN_WIDTH;
	settings.screenHeight = SCREEN_HEIGHT;

	Game game(settings);

	game.Run();

	return 0;
}