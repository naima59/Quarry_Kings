#include "gamestate.h"

//TODO CREATE PAUSE MENU
//TODO BALANCE THE GAME!
//TODO SHOW TIME ELAPSED IN MAIN GAME SCREEN
//TODO FIX CLOSING GAME\EXIT BUG
//CHERRY ON TOP --SHOW TOP 5 FASTEST RUNS (STORE RESULTS IN FILE? --PERSISTANCE?)

int main ()
{
	Gamestate gameStates;
	Game game;
	InitWindow(game.screenWidth, game.screenHeight, "Quarry Kings");
	while (!game.shouldExit || !WindowShouldClose())
	{
		gameStates.SceneManager();
	}

	return 0;
}