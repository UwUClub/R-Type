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
#include "Registry.hpp"

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
    bool isWindowReady();
    bool isWindowFullscreen();
    bool isWindowHidden();
    bool isWindowMinimized();
    bool isWindowMaximized();
    bool isWindowFocused();
    void setConfigFlags(ConfigFlags flags);
    bool isWindowResized();
    bool isWindowState(ConfigFlags flag);
    void setWindowState(ConfigFlags flag);
    void clearWindowState(ConfigFlags flags);
    void toggleFullscreen();
    void maximizeWindow();
    void minimizeWindow();
    void setWindowTitle(const std::string &title);
    int getScreenWidth();
    int getScreenHeight();
    int getRenderWidth();
    int getRenderHeight();
    int getMonitorWidth(int monitor);
    int getMonitorHeight(int monitor);
    int getMonitorRefreshRate(int monitor);
    int getCurrentMonitor();
    void setClipboardText(const std::string &text);
    std::string getClipboardText();
    void setWindowIcon(Image image);

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
    int getFPS();
    float getFrameTime();
    double getTime();

    // Misc. functions
    void takeScreenshot(const std::string &fileName);

    // Input-related functions: keyboard
    bool isKeyPressed(KeyboardKey key);
    bool isKeyDown(KeyboardKey key);
    bool isKeyReleased(KeyboardKey key);
    bool isKeyUp(KeyboardKey key);
    void setExitKey(KeyboardKey key);
    int getKeyPressed();
    int getCharPressed();

    // Input-related functions: mouse
    bool isMouseButtonPressed(MouseButton button);
    bool isMouseButtonDown(MouseButton button);
    bool isMouseButtonReleased(MouseButton button);
    bool isMouseButtonUp(MouseButton button);
    int getMouseX();
    int getMouseY();
    Vector2 getMousePosition();
    Vector2 getMouseDelta();
    void setMousePosition(int x, int y);
    void setMouseOffset(int offsetX, int offsetY);
    void setMouseScale(float scaleX, float scaleY);
    float getMouseWheelMove();
    Vector2 getMouseWheelMoveV();
    void setMouseCursor(int cursor);

    // Shapes-related functions
    void drawPixel(int posX, int posY, Color color);
    void drawCircle(int centerX, int centerY, float radius, Color color);
    void drawRectangle(int posX, int posY, int width, int height, Color color);

    // Color/pixel related functions
    Color fade(Color color, float alpha);
    int colorToInt(Color color);
    Vector4 colorNormalize(Color color);
    Color colorFromNormalized(Vector4 normalized);
    Color getColor(unsigned int hexValue);

    // Graphic classes

    class Image
    {
        public:
            Image(const std::string &fileName);
            Image(int width, int height, Color color);
            ~Image();
            bool isImageReady();
            void unloadImage();
            int getWidth() const;
            int getHeight() const;
            int getMipmaps() const;
            int getFormat() const;
            void *getData() const;

        private:
            ::Image _image;
    };

    class Sprite
    {
        public:
            Sprite(const std::string &fileName, float width, float height, std::size_t id);
            Sprite(Image image, float width, float height);
            unsigned int getId() const;
            float getWidth() const;
            float getHeight() const;
            int getTextureWidth() const;
            int getTextureHeight() const;
            int getMipmaps() const;
            int getFormat() const;
            void unloadSprite();

            // draw texture functions

            void draw(int posX, int posY, Color tint);
            void drawV(Raylib::Vector2 position, Color tint);
            void drawEx(Raylib::Vector2 position, float rotation, float scale, Color tint);
            void drawRec(Raylib::Rectangle source, Raylib::Vector2 position, Color tint);
            void drawPro(Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);

        private:
            void loadTextureFromImage(Image image);
            ::Texture2D _texture;
            // width and height in percentage of the screen
            float _width;
            float _height;
    };

    // Text functions and classes

    class Text
    {
        public:
            Text(std::string text, Vector2 position = {0, 0}, float fontSize = 5.0F, Color color = BLACK);
            void draw();
            void drawEx(float spacing);
            void drawPro(Vector2 origin, float rotation, float spacing);

            float x() const;
            float y() const;
            float getFontSize() const;
            void setFontSize(float fontSize);
            Vector2 getPosition() const;
            void setPixelPosition(Vector2 position);
            Color getColor() const;
            void setColor(Color color);
            void setCurrentFontSize(float fontSize);

        private:
            std::string _text;
            float _fontSize;
            float _currentFontSize;
            Color _color;
            Vector2 _position;
            Vector2 _pixelPosition;
    };

    void drawFPS(int posX, int posY);

} // namespace Raylib
