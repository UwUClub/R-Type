/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#include "SDLDisplayClass.hpp"

SDLDisplayClass::SDLDisplayClass()
{
    int windowFlags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return;
    }
    _window = SDL_CreateWindow("R-Type", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                               windowFlags);
    if (!_window) {
        printf("Failed to open SDL window: %s\n", SDL_GetError());
        return;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return;
    }
}

SDLDisplayClass::~SDLDisplayClass()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
