#include <iostream>
#include <string>

#include "lib.hpp"
#include "raylib/raylib.h"

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

struct FixedAtlas
{
    const Texture2D atlas;
    const int frame_width;
    const int frame_height;

    size_t frame;

    FixedAtlas(const Image & image, int width, int height)
        : atlas{ LoadTextureFromImage(image) }
        , frame_width{ atlas.width / width }
        , frame_height{ atlas.height / height }
        , frame{ 0u }
    { }

    ~FixedAtlas()
    {
        UnloadTexture(atlas);
    }

    void draw(const Vector2 & position, const Vector2 & scale, Color tint)
    {
        DrawTexturePro(
            atlas,
            {
                static_cast<float>(frame * frame_width),
                0,
                static_cast<float>(frame_width),
                static_cast<float>(frame_height)
            },
            {
                position.x,
                position.y,
                frame_width * scale.x,
                frame_height * scale.y
            },
            { 0, 0 },
            0.f,
            tint
        );
    }
};

auto main() -> int
{
    auto const lib = library {};
    auto const message = "Hello from " + lib.name + "!";
    std::cout << message << '\n';

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib demo");

    const auto image = LoadImage("assets/sprites/knight-run.png");
    auto animation = FixedAtlas{ image, 10, 1 };
    UnloadImage(image);

    SetTargetFPS(24);  // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        animation.frame += 1;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        animation.draw({ 0, 0 }, { 4.f, 4.f }, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
