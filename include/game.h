#ifndef GAME_H
#define GAME_H

//#include "raylib.h"
#include "resource_dir.h"
#include <math.h>
#include "gamestate.h"
#include "upgrades.h"

class Game
{
public:
    void InitLevel();
    void ProcessInput();
    void UnloadGame();
    
private:
    Texture2D ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight);
	const int screenWidth = 1024;
	const int screenHeight = 768;
    Texture2D backGroundTexture;
    Texture2D stoneTexture;
    Texture2D pickAxeTexture;
    Rectangle stoneBounds;
    Rectangle pickAxeBounds;
    Sound miningSound;
    int stoneWidth;
    int stoneHeight;
    int stoneX;
    int stoneY;
    int pickAxeX;
    int pickAxeY;
    float stoneCount;
    int stoneCountX;
    int stoneCountFontSize; 
    Upgrades upgradeOption;
    Upgrades::Resource pickAxeUpgrade;
    Upgrades upgradeUpdate;
};

#endif