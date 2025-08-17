#include "gamestate.h"

int main ()
{
	GameState gameStates;
	Game game;
	InitWindow(game.screenWidth, game.screenHeight, "Quarry Kings");
	while (!WindowShouldClose())
	{
		gameStates.SceneManager();
	}

	return 0;
}