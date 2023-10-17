/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadedSprite
*/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstddef>
#include <string>
#include <utility>

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
                : texture(nullptr),
                  rect(nullptr),
                  srcRect(nullptr)
            {}
            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the sprite
             * @param aTexture texture of the sprite (once loaded)
             * @param aTextureRect Size and position of the sprite in the texture
             * @param aDisplayRect Size and position of the sprite on the screen
             */
            LoadedSprite(std::string aPath, sf::Texture *aTexture, sf::IntRect *aTextureRect, sf::IntRect *aDisplayRect)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aTextureRect),
                  srcRect(aDisplayRect)
            {}

            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the sprite
             * @param aTexture texture of the sprite (once loaded)
             * @param aTextureRect Size and position of the sprite in the texture
             * @param aDisplayRect Size and position of the sprite on the screen
             */
            LoadedSprite(std::string aPath, sf::Texture *aTexture, sf::IntRect *aTextureRect, sf::IntRect *aDisplayRect,
                         float aScale)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aTextureRect),
                  srcRect(aDisplayRect),
                  scale(aScale)
            {}

            std::string path;
            sf::Texture *texture;
            sf::IntRect *rect;
            sf::IntRect *srcRect;
            float scale = 1.0;
    };
} // namespace Component
#endif // DEBUG