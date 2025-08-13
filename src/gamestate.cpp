#include "gamestate.h"

void Gamestate::SceneManager()
{
    while(gameState.InitSplashVictory == false)
    {
       gameState.InitSplashScreen();
    }
    while(gameState.SplashVictory == false)
    {
       gameState.SplashScreen();
    }
    while(gameState.InitLevelVictory == false)
    {
        gameState.InitLevel();
    }
    while(gameState.GameVictory == false)
    {
        gameState.ProcessInput();
    }
    gameState.UnloadGame();

}