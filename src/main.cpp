#include "raylib.h"
#include "resource_dir.h"
#include <math.h>

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SearchAndSetResourceDir("resources");

	const int screenWidth = 1024;
	const int screenHeight = 768;
	InitWindow(screenWidth, screenHeight, "Quarry Kings");
	SetTargetFPS(60);

	Image backgroundImage = LoadImage("back_ground.png");
	ImageResize(&backgroundImage, screenWidth, screenHeight);
	Texture2D backGroundTexture = LoadTextureFromImage(backgroundImage);
	UnloadImage(backgroundImage);

	int stoneWidth = 200;
	int stoneHeight = 200;
	Image stoneImage = LoadImage("stone.png");
	ImageResize(&stoneImage, stoneWidth, stoneHeight);
	Texture2D stoneTexture = LoadTextureFromImage(stoneImage);
	UnloadImage(stoneImage);

	int stoneX = (screenWidth / 2) - (stoneTexture.width / 2);
	int stoneY = (screenHeight / 2) - (stoneTexture.height / 2);
	Rectangle stoneBounds = { (float)stoneX, (float)stoneY, (float)stoneWidth, (float)stoneHeight };

	InitAudioDevice();
	Sound miningSound = LoadSound("mining.wav");
	SetSoundVolume(miningSound, 0.2f);

	int stoneCount = 0;
	while (!WindowShouldClose())
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
	}

	UnloadTexture(backGroundTexture);
	UnloadTexture(stoneTexture);
	UnloadSound(miningSound);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}