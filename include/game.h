#ifndef GAME_H
#define GAME_H

#include "upgrades.h"

class Game
{
public:
    void InitSplashScreen();
    void SplashScreen();
    void GameObjectiveSplashScreen();
    void InitLevel();
    void ProcessInput();
    void Victory();
    void UnloadGame();
    const int screenWidth = 1920;
	const int screenHeight = 1080;
    bool initSplashBool = false;
    bool splashBool = false;
    bool gameObjectiveSplashBool = false;
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

    std::vector<float> ReadTimesFromFile(const std::string& filename);
    std::string formatTime(float time);
    void WriteTimesToFile(const std::string& filename, const std::vector<float>& times);
    void UpdateFastestTimes(float newTime, const std::string& filename);
    void DrawFastestTimes(const std::string& filename, int x, int y, int fontSize);
    const std::string fastestTimesFile = "fastest_times.txt";
    
    Texture2D ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight);
    Texture2D splashTexture;
    Texture2D gameObjectiveTexture;
    Texture2D backGroundTexture;
    Texture2D victoryTexture;
    Texture2D pickaxeMouse;
    Texture2D stoneTexture;
    Texture2D pickaxeTexture;
    Texture2D villagerTexture;
    Texture2D oxenTexture;
    Texture2D cartTexture;
    std::vector<Texture2D> textures;

    Rectangle splashBounds;
    Rectangle gameObjectiveBounds;
    Rectangle victoryBounds;
    Rectangle newGameBounds;
    Rectangle stoneBounds;
    Rectangle pickaxeBounds;
    Rectangle villagerBounds;
    Rectangle oxenBounds;
    Rectangle cartBounds;

    bool newFastTimeSet = false;
    float stoneCount;
    float globalPerClick;
    float time;
    float lastTime;
    float timeElapsedFontSize;
    double gameElapsedTime;

    int stoneCountWholePart;
    int stoneCountDecimalPart;
    int splashX;
    int splashY;
    int gameObjectiveTextY;
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
    int cartX;
    int cartY;    
    int stoneCountX;
    int stoneCountY;
    int stoneCountFontSize;
    int globalPerSecond;
    int globalPerSecondX;
    int globalPerSecondY;
    int globalPerSecondFontSize;
    int globalPerClickX;
    int globalPerClickY;
    int globalPerClickFontSize;
    int timeElapsedX;
    int timeElapsedY;
    int fastestTimeX;
    int fastestTimeY;

    std::string formattedStoneCount;
    const char* gameObjectiveText;

    Upgrades upgradeOption;
    Upgrades::Resource pickaxeUpgrade;
    Upgrades::Resource villagerUpgrade;
    Upgrades::Resource oxenUpgrade;
    Upgrades::Resource cartUpgrade;
    Upgrades upgradeUpdate;
    
    Music music;
    Sound miningSound;
    Sound upgradeSound;
    Sound victorySound;
    Sound gameObjectiveSound;
};

#endif