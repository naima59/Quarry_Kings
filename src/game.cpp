#include "game.h"

Texture2D Game::ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight)
{
    Image imgToLoad = LoadImage(fileName);
    ImageResize(&imgToLoad, resizeWidth, resizeHeight);
    Texture2D NewTexture  = LoadTextureFromImage(imgToLoad);
    UnloadImage(imgToLoad);
    return NewTexture;
}

void Game::InitSplashScreen()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SearchAndSetResourceDir("resources");
    InitWindow(screenWidth, screenHeight, "Quarry Kings");
    HideCursor();
    SetTargetFPS(60);
    InitAudioDevice();

    //mouse pointer texture
    pickaxeMouse = ImageToTexture("pickaxeMouse.png", 100, 100);

    //splash screen
    splashTexture = ImageToTexture("Quarry_Kings_Splash.png", screenWidth, screenHeight);

    InitSplashVictory = true;
}

void Game::SplashScreen()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(splashTexture, 0, 0, WHITE);
    Vector2 mousePos = GetMousePosition();
    splashBounds = { 0.f, 0.f, (float)screenWidth, (float)screenHeight };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, splashBounds)) 
    {
        SplashVictory = true;
        std::cout << SplashVictory;
    }
    //MOUSE ICON
    DrawTexture(pickaxeMouse, mousePos.x, mousePos.y, WHITE);
    EndDrawing();

}

void Game::InitLevel()
{
    //load assets
    //background
    backGroundTexture = ImageToTexture("background.png", screenWidth, screenHeight);
    
    //clickable stone
    stoneWidth = 400;
	stoneHeight = 400;
    stoneTexture = ImageToTexture("stone.png", stoneWidth, stoneHeight);
	stoneX = (screenWidth / 2) - (stoneTexture.width / 2);
	stoneY = (screenHeight / 2) - (stoneTexture.height / 2);
	stoneBounds = { (float)stoneX, (float)stoneY, (float)stoneWidth, (float)stoneHeight };

    //pick axe upgrade
    int pickaxeWidth = 150;
    int pickaxeHeight = 150;
    pickaxeTexture = ImageToTexture("pickaxe.png", pickaxeWidth, pickaxeHeight);
	pickaxeX = (screenWidth / 4) - (pickaxeTexture.width / 2);
	pickaxeY = (screenHeight / 3) - (pickaxeTexture.height / 2);
	pickaxeBounds = {(float)pickaxeX, (float)pickaxeY, (float)pickaxeWidth, (float)pickaxeHeight};

    //villager upgrade
    int villagerWidth = 150;
    int villagerHeight = 150;
    villagerTexture = ImageToTexture("villager.png", villagerWidth, villagerHeight);
    villagerX = (screenWidth / 4) - (villagerTexture.width / 2);
    villagerY = ((screenHeight / 2) - (villagerTexture.height / 2)) + 30;
    villagerBounds = {(float)villagerX, (float)villagerY, (float)villagerWidth, (float)villagerHeight};

    //oxen upgrade
    int oxenWidth = 150;
    int oxenHeight = 150;
    oxenTexture = ImageToTexture("oxen.png", oxenWidth, oxenHeight);
    oxenX = (screenWidth / 4) - (oxenTexture.width / 2);
    oxenY = ((2 * screenHeight / 3) - (oxenTexture.height / 2)) + 60;
    oxenBounds = {(float)oxenX, (float)oxenY, (float)oxenWidth, (float)oxenHeight};
    
    //Load Upgrade Data
    pickaxeUpgrade = upgradeOption.resourceTypes("pickaxeQuality");
    villagerUpgrade = upgradeOption.resourceTypes("villager");
    oxenUpgrade = upgradeOption.resourceTypes("oxen");

    //stone count
    stoneCount = 0.f;
    const char* stoneCountText = TextFormat("Stone: %4.2f", stoneCount);
    stoneCountFontSize = 80;
    int stoneCountTextWidth = MeasureText(stoneCountText, stoneCountFontSize);
    stoneCountX = (screenWidth / 2) - (stoneCountTextWidth / 2);
    stoneCountY = (screenHeight / 10);

    //stone per second 
    globalPerSecond = 0.f;
    const char* globalPerSecondText = TextFormat("Per Second: %.2f", globalPerSecond);
    globalPerSecondFontSize = 40;
    int globalPerSecondTextWidth = MeasureText(globalPerSecondText, globalPerSecondFontSize);
    globalPerSecondX = (screenWidth / 2) - (globalPerSecondTextWidth / 2);
    globalPerSecondY = (screenHeight / 6);

    //stone per click
    globalPerClick = 1.f;
    const char* globalPerClickText = TextFormat("Per Click: %.2f", globalPerClick);
    globalPerClickFontSize = 40;
    int globalPerClickTextWidth = MeasureText(globalPerClickText, globalPerClickFontSize);
    globalPerClickX = (screenWidth / 2) - (globalPerClickTextWidth / 2);
    globalPerClickY = (2 * screenHeight / 10);
    
    //music
    music = LoadMusicStream("quarry_kings_music.wav");
    SetMusicVolume(music, 0.1f);
    PlayMusicStream(music);

    //sounds
    miningSound = LoadSound("mining.wav");
	SetSoundVolume(miningSound, 0.2f);

    lastTime = 0.0;
    InitLevelVictory = true;
};

void Game::ProcessInput()
{
    BeginDrawing();
    UpdateMusicStream(music);
    ClearBackground(RAYWHITE);
    Vector2 mousePos = GetMousePosition();

    //draw main textures
    DrawTexture(backGroundTexture, 0, 0, WHITE);
    DrawTexture(pickaxeTexture,pickaxeX,pickaxeY,WHITE);
    DrawTexture(villagerTexture,villagerX,villagerY,WHITE);
    DrawTexture(oxenTexture,oxenX,oxenY,WHITE);

    //variables that need to be updated
    float time = GetTime();
    float pulse = 0.5f + 0.5f * sinf(time * 4);
    bool isStoneHovered = CheckCollisionPointRec(mousePos, stoneBounds);
    globalPerSecond = upgradeUpdate.globalPerSecond;
    
    //mouse hover interaction
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
    
    //clickables (resource and upgrades)
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, stoneBounds)) 
    {
        stoneCount += globalPerClick;
        PlaySound(miningSound);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, pickaxeBounds)) 
    {
        upgradeUpdate.resourceManager(stoneCount, pickaxeUpgrade);
        globalPerClick = pickaxeUpgrade.amount;
        //TODO PLAY UPGRADE SOUND
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, villagerBounds)) 
    {
        upgradeUpdate.resourceManager(stoneCount, villagerUpgrade);
        //TODO PLAY UPGRADE SOUND
    } 
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, oxenBounds)) 
    {
        upgradeUpdate.resourceManager(stoneCount, oxenUpgrade);
        //TODO PLAY UPGRADE SOUND
    }
    
    //after upgrade checks
    if(time - lastTime >= 1.0)
    {
        stoneCount += globalPerSecond;
        lastTime = time;
    }

    if(stoneCount >= 1000000)
    {
        GameVictory = true;
    }
    
    //resource and upgrade text
    DrawText(TextFormat("Stone: %.2f", stoneCount), stoneCountX, stoneCountY, stoneCountFontSize, DARKGRAY);
    DrawText(TextFormat("Per Second: %.2f", globalPerSecond), globalPerSecondX, globalPerSecondY, globalPerSecondFontSize, DARKGRAY);
    DrawText(TextFormat("Per Click: %.2f", globalPerClick), globalPerClickX, globalPerClickY, globalPerClickFontSize, DARKGRAY);
    DrawText(TextFormat("Pickaxe Quality: %d", pickaxeUpgrade.level), pickaxeX, pickaxeY - 60, 35, DARKGRAY);
    DrawText(TextFormat("Cost: %d", pickaxeUpgrade.totalCost), pickaxeX, pickaxeY - 30, 35, DARKGRAY);
    DrawText(TextFormat("Villagers: %d", villagerUpgrade.level), villagerX, villagerY - 60, 35, DARKGRAY);
    DrawText(TextFormat("Cost: %d", villagerUpgrade.totalCost), villagerX, villagerY - 30, 35, DARKGRAY);
    DrawText(TextFormat("Oxen: %d", oxenUpgrade.level), oxenX, oxenY - 60, 35, DARKGRAY);
    DrawText(TextFormat("Cost: %d", oxenUpgrade.totalCost), oxenX, oxenY - 30, 35, DARKGRAY);

    //MOUSE ICON
    DrawTexture(pickaxeMouse, mousePos.x, mousePos.y, WHITE);
    EndDrawing();
};

void Game::UnloadGame()
{
    UnloadTexture(backGroundTexture);
	UnloadTexture(stoneTexture);
    UnloadTexture(pickaxeTexture);
    UnloadTexture(pickaxeMouse);
    UnloadMusicStream(music);
	UnloadSound(miningSound);
	CloseAudioDevice();
	CloseWindow();
};