/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadedSprite
*/

#include <string>
#include <utility>
#include <SDL_render.h>
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
            LoadedSprite(std::string aPath, SDL_Texture *aTexture, SDL_Rect *aTextureRect, SDL_Rect *aDisplayRect)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aTextureRect),
                  srcRect(aDisplayRect)
            {}
            std::string path;
            SDL_Texture *texture;
            SDL_Rect *rect;
            SDL_Rect *srcRect;
    };
} // namespace Component
#endif // DEBUG