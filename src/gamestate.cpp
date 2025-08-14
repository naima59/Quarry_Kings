#include "gamestate.h"

void Gamestate::SceneManager()
{
    while(!gameState.shouldExit && !WindowShouldClose())
    {
        if(!gameState.initSplashVictory)
        {
            gameState.InitSplashScreen();
        }
        else if(!gameState.splashVictory)
        {
            gameState.SplashScreen();
        }
        else if(!gameState.initLevelVictory)
        {
            gameState.InitLevel();
        }
        else if(!gameState.gameVictory)
        {
            gameState.ProcessInput();
        }
        else if(gameState.gameVictory)
        {
            gameState.Victory();
        }
    }
    gameState.UnloadGame();
}