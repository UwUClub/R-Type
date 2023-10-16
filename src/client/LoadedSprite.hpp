/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadedSprite
*/

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include "Raylib.hpp"

#ifndef LOADEDSPRITE_HPP
    #define LOADEDSPRITE_HPP

namespace Component {
    struct LoadedSprite
    {
            /**
             * @brief Construct a new Loaded Sprite object
             *
             */
            LoadedSprite()
                : texture(nullptr)
            {}
            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the sprite
             * @param aTexture texture of the sprite (once loaded)
             * @param aTextureRect Size and position of the sprite in the texture
             * @param aDisplayRect Size and position of the sprite on the screen
             */
            LoadedSprite(std::string aPath, Texture2D *aTexture, Rectangle aTextureRect, Rectangle aDisplayRect)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aTextureRect),
                  srcRect(aDisplayRect)
            {}

            std::string path;
            Texture2D *texture;
            Rectangle rect {};
            Rectangle srcRect {};
    };
} // namespace Component
#endif // DEBUG