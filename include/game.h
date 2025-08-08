#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "resource_dir.h"
#include <math.h>
#include "gamestate.h"
#include "upgrades.h"

class Game
{
public:
	const int screenWidth = 1024;
	const int screenHeight = 768;
    Texture2D backGroundTexture;
    Texture2D stoneTexture;
    Rectangle stoneBounds;
    Sound miningSound;
    int stoneWidth;
    int stoneHeight;
    int stoneX;
    int stoneY;
    int stoneCount;
    void InitLevel();
    void ProcessInput();
    void UnloadGame();
};

#endif