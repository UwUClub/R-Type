#include "Graphics.hpp"
#include "Geometry.hpp"
#include "Inputs.hpp"
#include "RayDisplayClass.hpp"

namespace Raylib {

    // Window-related functions

    void initWindow(int width, int height, const std::string &title)
    {
        InitWindow(width, height, title.c_str());
    }

    bool windowShouldClose()
    {
        return WindowShouldClose();
    }

    void closeWindow()
    {
        CloseWindow();
    }

    // Cursor-related functions

    void showCursor()
    {
        ShowCursor();
    }

    void hideCursor()
    {
        HideCursor();
    }

    bool isCursorHidden()
    {
        return IsCursorHidden();
    }

    void enableCursor()
    {
        EnableCursor();
    }

    void disableCursor()
    {
        DisableCursor();
    }

    bool isCursorOnScreen()
    {
        return IsCursorOnScreen();
    }

    // Drawing-related functions

    void clearBackground(Raylib::Color color)
    {
        ClearBackground({color.r, color.g, color.b, color.a});
    }

    void beginDrawing()
    {
        BeginDrawing();
    }

    void endDrawing()
    {
        EndDrawing();
    }

    // Timing-related functions

    void setTargetFPS(int fps)
    {
        SetTargetFPS(fps);
    }

    // Input-related functions: keyboard

    bool isKeyPressed(KeyboardKey key)
    {
        return IsKeyPressed(static_cast<int>(key));
    }

    bool isKeyDown(KeyboardKey key)
    {
        return IsKeyDown(static_cast<int>(key));
    }

    bool isKeyReleased(KeyboardKey key)
    {
        return IsKeyReleased(static_cast<int>(key));
    }

    bool isKeyUp(KeyboardKey key)
    {
        return IsKeyUp(static_cast<int>(key));
    }
    // Texture functions

    Sprite::Sprite()
        : _texture(nullptr),
          _source({0, 0, 0, 0})
    {}

    Sprite::Sprite(const std::string &fileName, const Raylib::Rectangle &source)
        : _fileName(fileName),
          _texture(nullptr),
          _source({source.x, source.y, source.width, source.height})
    {}

    Sprite::Sprite(const Sprite &sprite)
        : _fileName(sprite._fileName),
          _texture(sprite._texture),
          _source(sprite._source)
    {}

    Sprite &Sprite::operator=(const Sprite &sprite)
    {
        _fileName = sprite._fileName;
        _texture = sprite._texture;
        _source = sprite._source;
        return *this;
    }

    Sprite::Sprite(Sprite &&sprite) noexcept
        : _fileName(std::move(sprite._fileName)),
          _texture(std::move(sprite._texture)),
          _source(std::move(sprite._source))
    {}

    Sprite &Sprite::operator=(Sprite &&sprite) noexcept
    {
        _fileName = std::move(sprite._fileName);
        _texture = std::move(sprite._texture);
        _source = std::move(sprite._source);
        return *this;
    }

    void Sprite::loadTexture()
    {
        if (_texture != nullptr) {
            return;
        }
        _texture = RayDisplayClass::getInstance().getTexture(_fileName);
    }

    void Sprite::draw(Vector2 position, Color tint)
    {
        ::Vector2 pos = {position.x, position.y};
        ::Color tnt = {tint.r, tint.g, tint.b, tint.a};

        DrawTextureRec(*_texture, _source, pos, tnt);
    }

    void Sprite::unloadTexture(Texture2D texture)
    {
        UnloadTexture(texture);
    }
} // namespace Raylib
