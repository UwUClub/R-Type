/*
** EPITECH PROJECT, 2023
** R-Bus
** File description:
** Geometry
*/

#pragma once

#include <cstdint>
extern "C"
{
#include "raylib.h"
}

namespace Raylib {

    struct Vector2
    {
            Vector2(float x, float y);
            float x;
            float y;
    };

    struct Vector3
    {
            Vector3(float x, float y, float z);
            float x;
            float y;
            float z;
    };

    struct Vector4
    {
            Vector4(float x, float y, float z, float w);
            float x;
            float y;
            float z;
            float w;
    };

    struct Rectangle
    {
            Rectangle(float x, float y, float width, float height);
            float x;
            float y;
            float width;
            float height;
    };

    struct Color
    {
            Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
    };

    // COLOR CONSTANTS
    static const Color DarkGray = static_cast<Color>(DARKGRAY);
    static const Color Yellow = static_cast<Color>(YELLOW);
    static const Color Gold = static_cast<Color>(GOLD);
    static const Color Orange = static_cast<Color>(ORANGE);
    static const Color Pink = static_cast<Color>(PINK);
    static const Color Red = static_cast<Color>(RED);
    static const Color Maroon = static_cast<Color>(MAROON);
    static const Color Green = static_cast<Color>(GREEN);
    static const Color Lime = static_cast<Color>(LIME);
    static const Color DarkGreen = static_cast<Color>(DARKGREEN);
    static const Color SkyBlue = static_cast<Color>(SKYBLUE);
    static const Color Blue = static_cast<Color>(BLUE);
    static const Color DarkBlue = static_cast<Color>(DARKBLUE);
    static const Color Purple = static_cast<Color>(PURPLE);
    static const Color Violet = static_cast<Color>(VIOLET);
    static const Color DarkPurple = static_cast<Color>(DARKPURPLE);
    static const Color Beige = static_cast<Color>(BEIGE);
    static const Color Brown = static_cast<Color>(BROWN);
    static const Color DarkBrown = static_cast<Color>(DARKBROWN);
    static const Color White = static_cast<Color>(WHITE);
    static const Color Black = static_cast<Color>(BLACK);
    static const Color Blank = static_cast<Color>(BLANK);
    static const Color Magenta = static_cast<Color>(MAGENTA);
    static const Color RayWhite = static_cast<Color>(RAYWHITE);
} // namespace Raylib
