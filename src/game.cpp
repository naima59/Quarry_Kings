#include "game.h"

void Game::InitLevel()
{
    //basic config and setup
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SearchAndSetResourceDir("resources");
	InitWindow(screenWidth, screenHeight, "Quarry Kings");
	SetTargetFPS(60);
    InitAudioDevice();

    //load assets
    Image backgroundImage = LoadImage("back_ground.png");
	ImageResize(&backgroundImage, screenWidth, screenHeight);
	backGroundTexture = LoadTextureFromImage(backgroundImage);
	UnloadImage(backgroundImage);

	stoneWidth = 200;
	stoneHeight = 200;
	Image stoneImage = LoadImage("stone.png");
	ImageResize(&stoneImage, stoneWidth, stoneHeight);
	stoneTexture = LoadTextureFromImage(stoneImage);
	UnloadImage(stoneImage);

	stoneX = (screenWidth / 2) - (stoneTexture.width / 2);
	stoneY = (screenHeight / 2) - (stoneTexture.height / 2);
	stoneBounds = { (float)stoneX, (float)stoneY, (float)stoneWidth, (float)stoneHeight };
    
    miningSound = LoadSound("mining.wav");
	SetSoundVolume(miningSound, 0.2f);
    stoneCount = 0;
};

void Game::ProcessInput()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(backGroundTexture, 0, 0, WHITE);
    Vector2 mousePos = GetMousePosition();

    bool isHovered = CheckCollisionPointRec(mousePos, stoneBounds);
    float time = GetTime();
    float pulse = 0.5f + 0.5f * sinf(time * 4);

    if (isHovered) 
    {
        Color glowColor = { 255, 255, 0, (unsigned char)(pulse * 120) };
        float glowRadius = stoneWidth * (0.35f + 0.1f * pulse);
        DrawCircleV((Vector2){ float(stoneX + float(stoneWidth) / 2), float(stoneY + float(stoneHeight) / 2) }, glowRadius, glowColor);
        float scale = isHovered ? 1.1f : 1.0f; 
        float offsetY = isHovered ? -10.0f : 0.0f;

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
    DrawText(TextFormat("Stone: %d", stoneCount), 180, 180, 30, DARKGRAY);
    EndDrawing();
};

void Game::UnloadGame()
{
    UnloadTexture(backGroundTexture);
	UnloadTexture(stoneTexture);
	UnloadSound(miningSound);
	CloseAudioDevice();
	CloseWindow();
};