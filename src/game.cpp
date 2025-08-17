#include "game.h"

Texture2D Game::ImageToTexture(const char* fileName, int resizeWidth, int resizeHeight)
{
    Image imgToLoad = LoadImage(fileName);
    ImageResize(&imgToLoad, resizeWidth, resizeHeight);
    Texture2D NewTexture  = LoadTextureFromImage(imgToLoad);
    UnloadImage(imgToLoad);
    return NewTexture;
}

void Game::StartTimer(Timer *t) 
{
    if (t) 
    {
        t->start = GetTime();
        t->running = true;
    }
}

double Game::GetElapsed(Timer *t) 
{
    if (t && t->running) return GetTime() - t->start;
    return 0;
}

void Game::StopTimer(Timer *t) 
{
    if (t) t->running = false;
}

std::string Game::formatTime(float time) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << time;
    return stream.str();
}

std::vector<float> Game::ReadTimesFromFile(const std::string& filename) {
    std::vector<float> times;
    std::ifstream file(filename);
    float time;
    while (file >> time) {
        times.push_back(time);
    }
    return times;
}

void Game::WriteTimesToFile(const std::string& filename, const std::vector<float>& times) {
    std::ofstream file(filename);
    for (float t : times) {
        file << t << "\n";
    }
}

void Game::UpdateFastestTimes(float newTime, const std::string& filename) {
    std::vector<float> times = ReadTimesFromFile(filename);
    times.push_back(newTime);
    std::sort(times.begin(), times.end());
    if (times.size() > 5) times.resize(5); // Keep top 5
    WriteTimesToFile(filename, times);
}

void Game::DrawFastestTimes(const std::string& filename, int x, int y, int fontSize) {
    std::vector<float> times = ReadTimesFromFile(filename);
    for (size_t i = 0; i < times.size(); ++i) {
        std::string text = "Time " + std::to_string(i + 1) + ": " + formatTime(times[i]) + "s";
        DrawText(text.c_str(), x, y + i * (fontSize + 5), fontSize, WHITE);
    }
}

std::string formatWithCommas(int value) {
    std::string num = std::to_string(value);
    int insertPosition = num.length() - 3;
    while (insertPosition > 0) {
        num.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return num;
}

void Game::InitSplashScreen()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    SearchAndSetResourceDir("resources");
    Image icon = LoadImage("icon.png");
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
    UnloadImage(icon);
    HideCursor();
    SetTargetFPS(60);
    InitAudioDevice();

    //mouse pointer texture
    pickaxeMouse = ImageToTexture("pickaxeMouse.png", 100, 100);

    //splash screen
    splashTexture = ImageToTexture("Quarry_Kings_Splash.png", screenWidth, screenHeight);
    textures.push_back(splashTexture);
    splashX = 0;
    splashY = 0;
    splashBounds = { float(splashX), float(splashY), (float)screenWidth, (float)screenHeight };

    //game objective splash screen
    gameObjectiveTexture = ImageToTexture("Game_Objective_Splash.png", screenWidth, screenHeight);
    textures.push_back(gameObjectiveTexture);
    gameObjectiveBounds = { float(splashX), float(splashY), (float)screenWidth, (float)screenHeight };
    gameObjectiveText = R"(
        To the Esteemed Foreman of the Quarry,

        By decree of His Majesty, sovereign of these lands and protector of the realm, 
        
        thou art hereby commanded to extract one million stone from the royal quarry with utmost haste.

        This monumental harvest shall lay the foundation for a grand fortress -
        
        a bastion of strength to guard our borders and inspire our people.

        Tools, laborers, and provisions have been granted to aid thee in this noble endeavor. 
        
        Waste not a moment, for time is the enemy of progress.

        May your pick strike true and your will endure.

        - The King's Steward
        )";
    gameObjectiveTextY = GetScreenHeight();


    //START
    startFontSize = 90;
    int startTextWidth = MeasureText("START", startFontSize);
    startX = (screenWidth / 2) - (startTextWidth / 2);
    startY = (screenHeight / 2);

    //music
    music = LoadMusicStream("quarry_kings_music.wav");
    SetMusicVolume(music, 0.1f);
    PlayMusicStream(music);

    //sounds
    gameObjectiveSound = LoadSound("game_objective.wav");
    SetSoundVolume(gameObjectiveSound, 0.2f);
    miningSound = LoadSound("mining.wav");
	SetSoundVolume(miningSound, 0.2f);
    upgradeSound = LoadSound("upgrade.wav");
	SetSoundVolume(upgradeSound, 0.2f);
    victorySound = LoadSound("victory.wav");
    SetSoundVolume(victorySound, 0.2f);

    initSplashBool = true;
}

void Game::SplashScreen()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    UpdateMusicStream(music);
    DrawTexture(splashTexture, 0, 0, WHITE);
    PlaySound(gameObjectiveSound);

    //Start
    DrawText("START", startX, startY, startFontSize, WHITE);

    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, splashBounds)) 
    {
        splashBool = true;
    }

    //MOUSE ICON
    DrawTexture(pickaxeMouse, mousePos.x, mousePos.y, WHITE);
    EndDrawing();

}

void Game::GameObjectiveSplashScreen()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(gameObjectiveTexture, 0, 0, WHITE);
    Vector2 mousePos = GetMousePosition();

    if(!(gameObjectiveTextY < GetScreenHeight() / 4))
    {
        gameObjectiveTextY -= 1;
    }
    
    DrawText(gameObjectiveText, GetScreenWidth()/2 - MeasureText(gameObjectiveText, 30)/2, gameObjectiveTextY, 30, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, gameObjectiveBounds)) 
    {
        StopSound(gameObjectiveSound);
        gameObjectiveSplashBool = true;
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
    textures.push_back(backGroundTexture);
    
    victoryTexture = ImageToTexture("victory.png", screenWidth, screenHeight);
    textures.push_back(victoryTexture);
    victoryX = 0;
    victoryY = 0;
    victoryBounds = { float(victoryX), float(victoryY), (float)screenWidth, (float)screenHeight };

    //clickable stone
    stoneWidth = 400;
	stoneHeight = 400;
    stoneTexture = ImageToTexture("stone.png", stoneWidth, stoneHeight);
    textures.push_back(stoneTexture);
	stoneX = (screenWidth / 2) - (stoneTexture.width / 2);
	stoneY = (screenHeight / 2) - (stoneTexture.height / 2);
	stoneBounds = { (float)stoneX, (float)stoneY, (float)stoneWidth, (float)stoneHeight };

    //pick axe upgrade
    int pickaxeWidth = 150;
    int pickaxeHeight = 150;
    pickaxeTexture = ImageToTexture("pickaxe.png", pickaxeWidth, pickaxeHeight);
    textures.push_back(pickaxeTexture);
	pickaxeX = (screenWidth / 4) - (pickaxeTexture.width / 2);
	pickaxeY = (screenHeight / 4) - (pickaxeTexture.height / 2) - 100;
	pickaxeBounds = {(float)pickaxeX, (float)pickaxeY, (float)pickaxeWidth, (float)pickaxeHeight};

    //villager upgrade
    int villagerWidth = 150;
    int villagerHeight = 150;
    villagerTexture = ImageToTexture("villager.png", villagerWidth, villagerHeight);
    textures.push_back(villagerTexture);
    villagerX = (screenWidth / 4) - (villagerTexture.width / 2);
    villagerY = ((screenHeight / 4) - (villagerTexture.height / 2)) + 150;
    villagerBounds = {(float)villagerX, (float)villagerY, (float)villagerWidth, (float)villagerHeight};

    //cart upgrade
    int cartWidth = 150;
    int cartHeight = 150;
    cartTexture = ImageToTexture("cart.png", cartWidth, cartHeight);
    textures.push_back(cartTexture);
    cartX = (screenWidth / 4) - (cartTexture.width / 2);
    cartY = ((screenHeight / 4) - (cartTexture.height / 2)) + 400;
    cartBounds = {(float)cartX, (float)cartY, (float)cartWidth, (float)cartHeight};

    //oxen upgrade
    int oxenWidth = 150;
    int oxenHeight = 150;
    oxenTexture = ImageToTexture("oxen.png", oxenWidth, oxenHeight);
    textures.push_back(oxenTexture);
    oxenX = (screenWidth / 4) - (oxenTexture.width / 2);
    oxenY = ((screenHeight / 4) - (oxenTexture.height / 2)) + 650;
    oxenBounds = {(float)oxenX, (float)oxenY, (float)oxenWidth, (float)oxenHeight};
    
    //Load Upgrade Data
    pickaxeUpgrade = upgradeOption.ResourceTypes("pickaxeQuality");
    villagerUpgrade = upgradeOption.ResourceTypes("villager");
    oxenUpgrade = upgradeOption.ResourceTypes("oxen");
    cartUpgrade = upgradeOption.ResourceTypes("cart");

    //stone count
    stoneCount = 0.f;
    const char* stoneCountText = TextFormat("Stone: %7d", stoneCount);
    stoneCountFontSize = 80;
    int stoneCountTextWidth = MeasureText(stoneCountText, stoneCountFontSize);
    stoneCountX = (screenWidth / 2) - (stoneCountTextWidth / 2);
    stoneCountY = (screenHeight / 10);

    //stone per second 
    globalPerSecond = 0;
    const char* globalPerSecondText = TextFormat("Per Second: %2.2f", globalPerSecond);
    globalPerSecondFontSize = 40;
    int globalPerSecondTextWidth = MeasureText(globalPerSecondText, globalPerSecondFontSize);
    globalPerSecondX = (screenWidth / 2) - (globalPerSecondTextWidth / 2);
    globalPerSecondY = (stoneCountY + stoneCountFontSize);

    //stone per click
    globalPerClick = 1;

    //elapsed time
    const char* timeElapsed = TextFormat("Time Elapsed: %2.2f", gameElapsedTime);
    timeElapsedFontSize = 40;
    int timeElapsedTextWidth = MeasureText(timeElapsed, timeElapsedFontSize);
    timeElapsedX = (screenWidth / 2) - (timeElapsedTextWidth / 2);
    timeElapsedY = (globalPerSecondY + globalPerSecondFontSize);

    //fastest times
    fastestTimeX = (screenWidth / 4);
    fastestTimeY = (screenHeight / 9);

    //new game
    newGameFontSize = 90;
    int newGameTextWidth = MeasureText("NEW GAME", newGameFontSize);
    newGameX = (screenWidth / 2) - (newGameTextWidth / 2);
    newGameY = (screenHeight / 5 * 3);

    lastTime = 0.0;
    gameTimer = {0 };
    StartTimer(&gameTimer);
    initLevelBool = true;
};

void Game::ProcessInput()
{
    time = GetTime();
    float pulse = 1.f * sinf(time * 4);
    gameElapsedTime = GetElapsed(&gameTimer);
    BeginDrawing();
    UpdateMusicStream(music);
    ClearBackground(RAYWHITE);
    Vector2 mousePos = GetMousePosition();

    //draw main textures
    DrawTexture(backGroundTexture, 0, 0, WHITE);
    DrawTexture(pickaxeTexture,pickaxeX,pickaxeY,WHITE);
    DrawTexture(villagerTexture,villagerX,villagerY,WHITE);
    DrawTexture(cartTexture,cartX,cartY,WHITE);
    DrawTexture(oxenTexture,oxenX,oxenY,WHITE);

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
        if(pickaxeUpgrade.level == 0 && stoneCount >= pickaxeUpgrade.baseCost || pickaxeUpgrade.level != 0 && stoneCount >= pickaxeUpgrade.totalCost)
        {
            PlaySound(upgradeSound);
        }
        upgradeUpdate.ResourceManager(stoneCount, pickaxeUpgrade);

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, villagerBounds)) 
    {
        if(villagerUpgrade.level == 0 && stoneCount >= villagerUpgrade.baseCost || villagerUpgrade.level != 0 && stoneCount >= villagerUpgrade.totalCost)
        {
            PlaySound(upgradeSound);
        }
        upgradeUpdate.ResourceManager(stoneCount, villagerUpgrade);
    } 

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, cartBounds)) 
    {
        if(cartUpgrade.level == 0 && stoneCount >= cartUpgrade.baseCost || cartUpgrade.level != 0 && stoneCount >= cartUpgrade.totalCost)
        {
            PlaySound(upgradeSound);
        }
        upgradeUpdate.ResourceManager(stoneCount, cartUpgrade);
    }
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, oxenBounds)) 
    {
        if(oxenUpgrade.level == 0 && stoneCount >= oxenUpgrade.baseCost || oxenUpgrade.level != 0 && stoneCount >= oxenUpgrade.totalCost)
        {
            PlaySound(upgradeSound);
        }
        upgradeUpdate.ResourceManager(stoneCount, oxenUpgrade);
    }

    //after upgrade checks
    if(time - lastTime >= 1.0)
    {
        stoneCount += globalPerSecond;
        lastTime = time;
    }

    if(stoneCount >= 1000000)
    {
        StopTimer(&gameTimer);
        PlaySound(victorySound);
        gameVictory = true;
    }

    //stone count
    stoneCountWholePart = (int)stoneCount;
    formattedStoneCount = formatWithCommas(stoneCountWholePart);
    
    //resource and upgrade text
    DrawText(("Stone: " + formattedStoneCount).c_str(), stoneCountX, stoneCountY, stoneCountFontSize, WHITE);
    DrawText(TextFormat("Per Second: %d", globalPerSecond), globalPerSecondX, globalPerSecondY, globalPerSecondFontSize, WHITE);
    DrawText(TextFormat("Time Elapsed: %.2f", gameElapsedTime), timeElapsedX, timeElapsedY, timeElapsedFontSize, WHITE);
    DrawText(TextFormat("Pickaxe Quality: %d", pickaxeUpgrade.level), pickaxeX, pickaxeY - 60, 35, WHITE);
    DrawText(TextFormat("Cost: %d", pickaxeUpgrade.totalCost), pickaxeX, pickaxeY - 30, 35, WHITE);
    DrawText(TextFormat("Villagers: %d", villagerUpgrade.level), villagerX, villagerY - 60, 35, WHITE);
    DrawText(TextFormat("Cost: %d", villagerUpgrade.totalCost), villagerX, villagerY - 30, 35, WHITE);
    DrawText(TextFormat("Cart: %d", cartUpgrade.level), cartX, cartY - 60, 35, WHITE);
    DrawText(TextFormat("Cost: %d", cartUpgrade.totalCost), cartX, cartY - 30, 35, WHITE);
    DrawText(TextFormat("Oxen: %d", oxenUpgrade.level), oxenX, oxenY - 60, 35, WHITE);
    DrawText(TextFormat("Cost: %d", oxenUpgrade.totalCost), oxenX, oxenY - 30, 35, WHITE);

    //MOUSE ICON
    DrawTexture(pickaxeMouse, mousePos.x, mousePos.y, WHITE);
    EndDrawing();
};

void Game::Victory()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if(!newFastTimeSet)
    {
        UpdateFastestTimes(time,  fastestTimesFile);
        newFastTimeSet = true;
    }
    
    Vector2 mousePos = GetMousePosition();
    DrawTexture(victoryTexture, 0, 0, WHITE);

    //NEW GAME
    DrawText("NEW GAME", newGameX, newGameY, newGameFontSize, WHITE);
    DrawText(TextFormat("Time Elapsed: %.2f", time), timeElapsedX, newGameY + newGameFontSize, timeElapsedFontSize, WHITE);
    DrawText("Fastest Times:", fastestTimeX, fastestTimeY - 40, 40, WHITE);
    DrawFastestTimes(fastestTimesFile, fastestTimeX, fastestTimeY, 40);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, victoryBounds)) 
    {
        stoneCount = 0;
        globalPerClick = 1.f;
        globalPerSecond = 0;
        upgradeUpdate.globalPerSecond = 0;
        pickaxeUpgrade.level = 0;
        pickaxeUpgrade.totalCost = pickaxeUpgrade.baseCost;
        villagerUpgrade.level = 0;
        villagerUpgrade.totalCost = villagerUpgrade.baseCost;
        oxenUpgrade.level = 0;
        oxenUpgrade.totalCost = villagerUpgrade.baseCost;  
        cartUpgrade.level = 0;
        cartUpgrade.totalCost = villagerUpgrade.baseCost;
        lastTime = 0.0;
        gameTimer = {0 };
        StartTimer(&gameTimer);              
        gameVictory = false;
    }

    //MOUSE ICON
    DrawTexture(pickaxeMouse, mousePos.x, mousePos.y, WHITE);

    EndDrawing();
};

void Game::UnloadGame()
{
    for(int i = 0; i < textures.size(); i++)
    {
        UnloadTexture(textures[i]);
    }
    UnloadMusicStream(music);
    UnloadSound(victorySound);
    UnloadSound(upgradeSound);
	UnloadSound(miningSound);
    UnloadSound(gameObjectiveSound);
    
	CloseAudioDevice();
	CloseWindow();
};