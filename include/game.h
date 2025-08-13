#ifndef GAME_H
#define GAME_H

//#include "raylib.h"
#include "resource_dir.h"
#include <math.h>
#include "upgrades.h"

class Game
{
public:
    void InitSplashScreen();
    void SplashScreen();
    void InitLevel();
    void ProcessInput();
    void UnloadGame();
    bool InitSplashVictory = false;
    bool SplashVictory = false;
    bool InitLevelVictory = false;
    bool GameVictory = false;
    
private:
    Texture2D ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight);
	const int screenWidth = 1920;
	const int screenHeight = 1080;
    Texture2D splashTexture;
    Texture2D backGroundTexture;
    Texture2D pickaxeMouse;
    Texture2D stoneTexture;
    Texture2D pickaxeTexture;
    Texture2D villagerTexture;
    Texture2D oxenTexture;
    Rectangle splashBounds;
    Rectangle stoneBounds;
    Rectangle pickaxeBounds;
    Rectangle villagerBounds;
    Rectangle oxenBounds;
    float stoneCount;
    float globalPerSecond;
    float globalPerClick;
    double lastTime;
    int stoneWidth;
    int stoneHeight;
    int stoneX;
    int stoneY;
    int pickaxeX;
    int pickaxeY;
    int villagerX;
    int villagerY;
    int oxenX;
    int oxenY;
    int stoneCountX;
    int stoneCountY;
    int stoneCountFontSize;
    int globalPerSecondX;
    int globalPerSecondY;
    int globalPerSecondFontSize;
    int globalPerClickX;
    int globalPerClickY;
    int globalPerClickFontSize;

    Upgrades upgradeOption;
    Upgrades::Resource pickaxeUpgrade;
    Upgrades::Resource villagerUpgrade;
    Upgrades::Resource oxenUpgrade;
    Upgrades upgradeUpdate;
    
    Music music;
    Sound miningSound;
};

#endif