#ifndef GAME_H
#define GAME_H

#include "upgrades.h"

class Game
{
public:
    void InitSplashScreen();
    void SplashScreen();
    void InitLevel();
    void ProcessInput();
    void Victory();
    void UnloadGame();
    const int screenWidth = 1920;
	const int screenHeight = 1080;
    bool initSplashBool = false;
    bool splashBool = false;
    bool initLevelBool = false;
    bool gameVictory = false;
    bool restartGame = false;
    
private:
    typedef struct {
        double start;
        bool running;
    } Timer;

    void StartTimer(Timer *t);
    double GetElapsed(Timer *t);
    void StopTimer(Timer *t);
    Timer gameTimer;
    
    Texture2D ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight);
    Texture2D splashTexture;
    Texture2D backGroundTexture;
    Texture2D victoryTexture;
    Texture2D pickaxeMouse;
    Texture2D stoneTexture;
    Texture2D pickaxeTexture;
    Texture2D villagerTexture;
    Texture2D oxenTexture;
    std::vector<Texture2D> textures;

    Rectangle splashBounds;
    Rectangle victoryBounds;
    Rectangle newGameBounds;
    Rectangle stoneBounds;
    Rectangle pickaxeBounds;
    Rectangle villagerBounds;
    Rectangle oxenBounds;

    float stoneCount;
    float globalPerSecond;
    float globalPerClick;
    float time;
    float lastTime;
    float timeElapsedFontSize;
    double gameElapsedTime;

    int splashX;
    int splashY;
    int victoryX;
    int victoryY;
    int startX;
    int startY;
    int newGameX;
    int newGameY;
    int startFontSize;
    int newGameFontSize;
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
    int timeElapsedX;
    int timeElapsedY;

    Upgrades upgradeOption;
    Upgrades::Resource pickaxeUpgrade;
    Upgrades::Resource villagerUpgrade;
    Upgrades::Resource oxenUpgrade;
    Upgrades upgradeUpdate;
    
    Music music;
    Sound miningSound;
    Sound upgradeSound;
    Sound victorySound;
};

#endif