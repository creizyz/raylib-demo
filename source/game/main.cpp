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

enum class State
{
    IDLE,
    WALKING,
    RUNNING,
    JUMPING,
    FALLING,
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

    State state = State::IDLE;
    Vector2 position = { 0.f, 0.f };
    Vector2 velocity = { 0.f, 0.f };
    float direction = 1.f;

    SetTargetFPS(24);  // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        auto dT = GetFrameTime();

        // update state
        if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
        {
            state = State::WALKING;
            direction = -1.f;
        }
        else if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
        {
            state = State::WALKING;
            direction = 1.f;
        }
        else
        {
            state = State::IDLE;
        }

        // update velocity
        switch (state)
        {
            case State::WALKING:
                velocity.x = 250.f;
                animation.frame += 1;
                break;
            case State::IDLE:
                velocity.x = 0.f;
                animation.frame = 2;
                break;
            default:
                break;
        }

        // update position
        position.x += direction * velocity.x * dT;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        animation.draw(position, { 4.f, 4.f }, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
