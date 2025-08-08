#include "game.h"

int main ()
{
	Game stoneAge;
	stoneAge.InitLevel();
	while (!WindowShouldClose())
	{
		stoneAge.ProcessInput();
	}

	stoneAge.UnloadGame();
	return 0;
}