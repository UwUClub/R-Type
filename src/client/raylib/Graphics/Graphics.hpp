/*
** EPITECH PROJECT, 2023
** R-Bus
** File description:
** Graphics
*/

#pragma once

#include <string>
extern "C"
{
#include "raylib.h"
}
#include "Geometry.hpp"
#include "Inputs.hpp"

namespace Raylib {

    enum class ConfigFlags
    {
        VSYNC_HINT = FLAG_VSYNC_HINT,
        FULLSCREEN_MODE = FLAG_FULLSCREEN_MODE,
        WINDOW_RESIZABLE = FLAG_WINDOW_RESIZABLE,
        WINDOW_UNDECORATED = FLAG_WINDOW_UNDECORATED,
        WINDOW_HIDDEN = FLAG_WINDOW_HIDDEN,
        WINDOW_MINIMIZED = FLAG_WINDOW_MINIMIZED,
        WINDOW_MAXIMIZED = FLAG_WINDOW_MAXIMIZED,
        WINDOW_UNFOCUSED = FLAG_WINDOW_UNFOCUSED,
        WINDOW_TOPMOST = FLAG_WINDOW_TOPMOST,
        WINDOW_ALWAYS_RUN = FLAG_WINDOW_ALWAYS_RUN,
        WINDOW_TRANSPARENT = FLAG_WINDOW_TRANSPARENT,
        WINDOW_HIGHDPI = FLAG_WINDOW_HIGHDPI,
        WINDOW_MOUSE_PASSTHROUGH = FLAG_WINDOW_MOUSE_PASSTHROUGH,
        MSAA_4X_HINT = FLAG_MSAA_4X_HINT,
        INTERLACED_HINT = FLAG_INTERLACED_HINT,
    };

    // Window-related functions
    void initWindow(int width, int height, const std::string &title);
    bool windowShouldClose();
    void closeWindow();

    // Cursor-related functions
    void showCursor();
    void hideCursor();
    bool isCursorHidden();
    void enableCursor();
    void disableCursor();
    bool isCursorOnScreen();

    // Drawing-related functions
    void clearBackground(Raylib::Color color);
    void beginDrawing();
    void endDrawing();

    // Timing-related functions
    void setTargetFPS(int fps);

    // Input-related functions: keyboard
    bool isKeyPressed(KeyboardKey key);
    bool isKeyDown(KeyboardKey key);
    bool isKeyReleased(KeyboardKey key);
    bool isKeyUp(KeyboardKey key);

    class Sprite
    {
        public:
            Sprite();
            Sprite(const std::string &fileName, const Rectangle &source);

            Sprite(const Sprite &sprite);
            Sprite &operator=(const Sprite &sprite);

            Sprite(Sprite &&sprite) noexcept;
            Sprite &operator=(Sprite &&sprite) noexcept;
            void unloadSprite();
            void loadTexture();

            void draw(Vector2 position, Color tint);

            static void unloadTexture(Texture2D texture);

        public:
            std::string _fileName;
            Texture2D *_texture;
            // width and height in percentage of the screen
            ::Rectangle _source;
    };
} // namespace Raylib
