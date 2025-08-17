#include "gamestate.h"

void GameState::SceneManager()
{
    //initialize splash screen
    if(!gameState.initSplashBool)
    {
        gameState.InitSplashScreen();
    }
    //splash screen
    else if(!gameState.splashBool)
    {
        gameState.SplashScreen();
    }
    //initialize game level
    else if(!gameState.gameObjectiveSplashBool)
    {
        gameState.GameObjectiveSplashScreen();
    }
    else if(!gameState.initLevelBool)
    {
        gameState.InitLevel();
    }
    //game
    else if(!gameState.gameVictory)
    {
        gameState.ProcessInput();
    }
    //victory screen
    else if(gameState.gameVictory)
    {
        gameState.Victory();
    }
    else 
    {
        gameState.UnloadGame();
    }
    
}