/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#include "SDLDisplayClass.hpp"
#include <algorithm>
#include "SparseArray.hpp"
#include "Utils.hpp"
#include "World.hpp"

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
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return;
    }
}

void SDLDisplayClass::addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                Component::LoadedSprite aSprite)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.getComponent<ECS::Utils::Vector2f>();
    auto &spd = world.getComponent<Component::Speed>();
    auto &type = world.getComponent<Component::TypeEntity>();
    auto &sprite = world.getComponent<Component::LoadedSprite>();
    size_t idx = world.createEntity();

    vec.insertAt(idx, aPos);
    spd.insertAt(idx, aSpeed);
    type.insertAt(idx, aType);
    sprite.insertAt(idx, aSprite);
}

SDLDisplayClass::~SDLDisplayClass()
{
    auto &world = ECS::Core::World::getInstance();
    auto &sprites = world.getComponent<Component::LoadedSprite>();

    for (auto &sprite : sprites) {
        if (!sprite.has_value()) {
            continue;
        }
        SDL_DestroyTexture(sprite->texture);
    }

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
