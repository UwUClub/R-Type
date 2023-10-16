/*
** EPITECH PROJECT, 2023
** R-Bus
** File description:
** Geometry
*/

#include "Geometry.hpp"

namespace Raylib {

    Vector2::Vector2(float x, float y)
        : x(x),
          y(y)
    {}

    Vector3::Vector3(float x, float y, float z)
        : x(x),
          y(y),
          z(z)
    {}

    Vector4::Vector4(float x, float y, float z, float w)
        : x(x),
          y(y),
          z(z),
          w(w)
    {}

    Rectangle::Rectangle(float x, float y, float width, float height)
        : x(x),
          y(y),
          width(width),
          height(height)
    {}

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r),
          g(g),
          b(b),
          a(a)
    {}
} // namespace Raylib
