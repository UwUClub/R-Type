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
                : texture(nullptr),
                  rect({0, 0, 0, 0}),
                  srcRect({0, 0, 0, 0})
            {}
            LoadedSprite(std::string aPath, SDL_Texture *aTexture, SDL_Rect aTextureRect, SDL_Rect aDisplayRect)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(aTextureRect),
                  srcRect(aDisplayRect)
            {}
            std::string path;
            SDL_Texture *texture;
            SDL_Rect rect;
            SDL_Rect srcRect;
    };
} // namespace Component
#endif // DEBUG