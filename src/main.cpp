#include <cstdlib>
#include <cstdio>
#include "raylib.h"


int main()
{
    int width{800};
    int height{450};

    int circleX = width / 4;
    int circleY = height / 2;
    int circleRadius{25};

    int circleXLeft = circleX - circleRadius;
    int circleXRight = circleX + circleRadius;
    int circleYTop = circleY - circleRadius;
    int circleYBottom = circleY + circleRadius;

    int axaX{400};
    int axaY{0};
    int axaWidth{50};
    int axaHeight{50};
    int axaDirection{10};

    int axaXLeft = axaX;
    int axaXRight = axaX + axaWidth;
    int axaYTop = axaY;
    int axaYBottom = axaY + axaHeight;

    bool collisionWithAxe{true};

    InitWindow(width, height, "Demo Window");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        collisionWithAxe = axaYBottom >= circleYTop
                           && axaYTop <= circleYBottom
                           && axaXLeft <= circleXRight
                           && axaXRight >= circleXLeft;

        if (collisionWithAxe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {

            circleXLeft = circleX - circleRadius;
            circleXRight = circleX + circleRadius;
            circleYTop = circleY - circleRadius;
            circleYBottom = circleY + circleRadius;

            axaXLeft = axaX;
            axaXRight = axaX + axaWidth;
            axaYTop = axaY;
            axaYBottom = axaY + axaHeight;

            DrawCircle(circleX, circleY, circleRadius, BLUE);
            DrawRectangle(axaX, axaY, axaWidth, axaHeight, RED);

            axaY += axaDirection;
            if (axaY > (height - axaHeight) || axaY < 0)
            {
                axaDirection *= -1;
            }


            if (IsKeyDown(KEY_D) && circleX < width)
            {
                circleX += 10;
            }
            else if (IsKeyDown(KEY_A) && circleX > 0)
            {
                circleX -= 10;
            }
        }

        EndDrawing();

    }
}