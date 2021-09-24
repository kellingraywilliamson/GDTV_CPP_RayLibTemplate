#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= (float) windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.f;
        data.rec.x = (float) data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    const int WINDOW_DIMENSIONS[] = {512, 380};
    const float BACKGROUND_SCALE{2.f};
    const int BACKGROUND_SPEED{20};
    const float MIDGROUND_SCALE{2.f};
    const int MIDGROUND_SPEED{30};
    const float FOREGROUND_SCALE{2.f};
    const int FOREGROUND_SPEED{40};
    const int GRAVITY{1'000};
    const int JUMP_VELOCITY{-600};
    const int NEBULA_VELOCITY{-200};
    const int SIZE_OF_NEBULAE{6};

    float runVelocity{0.f};
    float bgX{0.f};
    float midX{0.f};
    float foreX{0.f};
    bool collision{};

    // initialize the window
    InitWindow(WINDOW_DIMENSIONS[0], WINDOW_DIMENSIONS[1], "Dapper Dasher!");
    SetTargetFPS(60);

    Texture2D nebula = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/textures/12_nebula_spritesheet.png");
    Texture2D scarfy = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/textures/scarfy.png");
    Texture2D background = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/textures/far-buildings.png");
    Texture2D midground = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/textures/back-buildings.png");
    Texture2D foreground = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/textures/foreground.png");

    AnimData nebulae[SIZE_OF_NEBULAE]{};
    AnimData scarfyData{
            {0.f, 0.f, (float) scarfy.width / 6.f, (float) scarfy.height},
            {(float) WINDOW_DIMENSIONS[0] / 2.f - scarfyData.rec.width / 2.f,
             (float) WINDOW_DIMENSIONS[1] - scarfyData.rec.height},
            0,
            1.f / 12.f,
            0.f
    };

    for (int i = 0; i < SIZE_OF_NEBULAE; ++i)
    {
        nebulae[i].rec.x = 0.f;
        nebulae[i].rec.y = 0.f;
        nebulae[i].rec.width = (float) nebula.width / 8.f;
        nebulae[i].rec.height = (float) nebula.height / 8.f;
        nebulae[i].pos.x = (float) WINDOW_DIMENSIONS[0] + (float) (300 * i);
        nebulae[i].pos.y = (float) WINDOW_DIMENSIONS[1] - (float) nebula.height / 8.f;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.f;
        nebulae[i].updateTime = 0.f / 12.f;
    }

    float finishLine{nebulae[SIZE_OF_NEBULAE - 1].pos.x};

    while (!WindowShouldClose())
    {
        // is the rectanlge in the air?
        bool isInAir{};
        // delta time (time since last frame)
        const float DELTA_TIME{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= BACKGROUND_SPEED * DELTA_TIME;
        if (bgX <= (float) -background.width * BACKGROUND_SCALE)
        {
            bgX = 0;
        }
        Vector2 bg1Pos{bgX, 0.f};
        DrawTextureEx(background, bg1Pos, 0.f, BACKGROUND_SCALE, WHITE);
        Vector2 bg2Pos{bgX + (float) background.width * BACKGROUND_SCALE, 0.f};
        DrawTextureEx(background, bg2Pos, 0.f, BACKGROUND_SCALE, WHITE);


        midX -= MIDGROUND_SPEED * DELTA_TIME;
        if (midX <= (float) -midground.width * MIDGROUND_SCALE)
        {
            midX = 0.f;
        }

        foreX -= FOREGROUND_SPEED * DELTA_TIME;
        if (foreX <= (float) -foreground.width * FOREGROUND_SCALE)
        {
            foreX = 0.f;
        }


        Vector2 mid1Pos{midX, 0.f};
        Vector2 mid2Pos{midX + (float) midground.width * MIDGROUND_SCALE};
        DrawTextureEx(midground, mid1Pos, 0.f, BACKGROUND_SCALE, WHITE);
        DrawTextureEx(midground, mid2Pos, 0.f, MIDGROUND_SCALE, WHITE);

        Vector2 forePos{foreX, 0.f};
        Vector2 fore2Pos{foreX + (float) foreground.width * FOREGROUND_SCALE};
        DrawTextureEx(foreground, forePos, 0.f, FOREGROUND_SCALE, WHITE);
        DrawTextureEx(foreground, fore2Pos, 0.f, FOREGROUND_SCALE, WHITE);

        // perform ground check
        if (isOnGround(scarfyData, WINDOW_DIMENSIONS[1]))
        {
            // rectangle is on the ground
            runVelocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            runVelocity += GRAVITY * DELTA_TIME;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            runVelocity += JUMP_VELOCITY;
        }

        for (int i = 0; i < SIZE_OF_NEBULAE; ++i)
        {
            nebulae[i].pos.x += (float) NEBULA_VELOCITY * DELTA_TIME;
        }

        finishLine += NEBULA_VELOCITY * DELTA_TIME;

        // update scarfy position
        scarfyData.pos.y += (float) runVelocity * DELTA_TIME;

        // update scarfy's animation frame
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, DELTA_TIME, 5);
        }
        // update nebula animation frame
        for (int i = 0; i < SIZE_OF_NEBULAE; ++i)
        {
            nebulae[i] = updateAnimData(nebulae[i], DELTA_TIME, 8);
        }


        for (AnimData nebula: nebulae)
        {
            float pad{20.f};
            Rectangle nebRect{
                    nebula.pos.x + pad,
                    nebula.pos.y + pad,
                    nebula.rec.width - 2 * pad,
                    nebula.rec.height - 2 * pad
            };
            Rectangle scarfyRect{
                    scarfyData.pos.x,
                    scarfyData.pos.y,
                    scarfyData.rec.width,
                    scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRect, scarfyRect))
            {
                collision = true;
            }
        }


        if (collision)
        {
            DrawText("Game Over!", WINDOW_DIMENSIONS[0] / 4, WINDOW_DIMENSIONS[1] / 2, 40, RED);
        }
        else if (finishLine < scarfyData.pos.x)
        {
            DrawText("You Win!", WINDOW_DIMENSIONS[0] / 4, WINDOW_DIMENSIONS[1] / 2, 40, WHITE);
        }
        else
        {
            for (int i = 0; i < SIZE_OF_NEBULAE; ++i)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }
        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}
