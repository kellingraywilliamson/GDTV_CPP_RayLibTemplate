#include "raylib.h"


int main()
{
    const int SCREEN_WIDTH{384};
    const int SCREEN_HEIGHT{450};
    const float MAP_SCALE{4.f};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Top Down Tiles");
    SetTargetFPS(60);

    Texture2D map = LoadTexture(
            "/Users/adamkellingray-williamson/Developer/GitHub/GDTV_CPP_RayLibTemplate/src/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.f, 0.f};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureEx(map, mapPos, 0.f, MAP_SCALE, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();

    return 0;
}
