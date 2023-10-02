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
            LoadedSprite()
                : path(""),
                  texture(nullptr),
                  rect(nullptr),
                  srcRect(nullptr)
            {}
            LoadedSprite(std::string aPath, SDL_Texture *aTexture, SDL_Rect *aRect, SDL_Rect *aSrcRect)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aRect),
                  srcRect(aSrcRect)
            {}
            std::string path;
            SDL_Texture *texture;
            SDL_Rect *rect;
            SDL_Rect *srcRect;
    };
} // namespace Component
#endif // DEBUG