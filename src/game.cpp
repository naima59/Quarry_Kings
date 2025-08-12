#include "game.h"

Texture2D Game::ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight)
{
    Image imgToLoad = LoadImage(fileName);
    ImageResize(&imgToLoad, resizeWidth, resizeHeight);
    Texture2D NewTexture  = LoadTextureFromImage(imgToLoad);
    UnloadImage(imgToLoad);
    return NewTexture;
}

void Game::InitLevel()
{
    //basic config and setup
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SearchAndSetResourceDir("resources");
	InitWindow(screenWidth, screenHeight, "Quarry Kings");
	SetTargetFPS(60);
    InitAudioDevice();

    //load assets
    //background
    backGroundTexture = ImageToTexture("back_ground.png", screenWidth, screenHeight);
    
    //clickable stone
    stoneWidth = 200;
	stoneHeight = 200;
    stoneTexture = ImageToTexture("stone.png", stoneWidth, stoneHeight);
	stoneX = (screenWidth / 2) - (stoneTexture.width / 2);
	stoneY = (screenHeight / 2) - (stoneTexture.height / 2);
	stoneBounds = { (float)stoneX, (float)stoneY, (float)stoneWidth, (float)stoneHeight };

    //pick axe upgrade
    int pickAxeWidth = 100;
    int pickAxeHeight = 100;
    pickAxeTexture = ImageToTexture("pickaxe.png", pickAxeWidth, pickAxeHeight);
	pickAxeX = (screenWidth / 2) - (stoneTexture.width / 2) - 175;
	pickAxeY = (screenHeight / 2) - (stoneTexture.height / 2) - 25;
	pickAxeBounds = {(float)pickAxeX, (float)pickAxeY, (float)pickAxeWidth, (float)pickAxeHeight};
    
    pickAxeUpgrade = upgradeOption.resourceTypes("pickAxeQuality");

    //resource counter (stone)
    stoneCount = 0.f;
    const char* stoneCountText = TextFormat("Stone: %d", stoneCount);
    stoneCountFontSize = 80;
    int stoneCountTextWidth = MeasureText(stoneCountText, stoneCountFontSize);
    stoneCountX = (screenWidth / 2) - (stoneCountTextWidth / 2);
    
    //sounds
    miningSound = LoadSound("mining.wav");
	SetSoundVolume(miningSound, 0.2f);
};

void Game::ProcessInput()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(backGroundTexture, 0, 0, WHITE);
    DrawTexture(pickAxeTexture,pickAxeX,pickAxeY,WHITE);
    float time = GetTime();
    float pulse = 0.5f + 0.5f * sinf(time * 4);

    Vector2 mousePos = GetMousePosition();
    bool isStoneHovered = CheckCollisionPointRec(mousePos, stoneBounds);


    if (isStoneHovered) 
    {
        Color glowColor = { 255, 255, 0, (unsigned char)(pulse * 120) };
        float glowRadius = stoneWidth * (0.35f + 0.1f * pulse);
        DrawCircleV((Vector2){ float(stoneX + float(stoneWidth) / 2), float(stoneY + float(stoneHeight) / 2) }, glowRadius, glowColor);
        float scale = isStoneHovered ? 1.1f : 1.0f; 
        float offsetY = isStoneHovered ? -10.0f : 0.0f;

        Vector2 origin = { stoneTexture.width / 2.0f, stoneTexture.height / 2.0f };
        Vector2 position = { float(stoneX), stoneY + offsetY };
        DrawTextureEx(stoneTexture, position, 0.0f, scale, WHITE);
    }
    else 
    {
        DrawTexture(stoneTexture, stoneX, stoneY, WHITE);
    }		
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, stoneBounds)) 
    {
        stoneCount++;
        PlaySound(miningSound);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, pickAxeBounds)) 
    {
        upgradeUpdate.resourceManager(stoneCount, pickAxeUpgrade);
        //PlaySound(miningSound);
    }
    

    stoneCount = stoneCount += pickAxeUpgrade.perSecond;
    
    DrawText(TextFormat("Stone: %.2f", stoneCount), stoneCountX, 180, stoneCountFontSize, DARKGRAY);
    EndDrawing();
};

void Game::UnloadGame()
{
    UnloadTexture(backGroundTexture);
	UnloadTexture(stoneTexture);
    UnloadTexture(pickAxeTexture);
	UnloadSound(miningSound);
	CloseAudioDevice();
	CloseWindow();
};