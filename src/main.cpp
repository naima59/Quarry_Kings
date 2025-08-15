#include "gamestate.h"

//CHERRY ON TOP --SHOW TOP 5 FASTEST RUNS (STORE RESULTS IN FILE? --PERSISTANCE?)
//REVIEW pow(resourceType.rateScale, resourceType.level);

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