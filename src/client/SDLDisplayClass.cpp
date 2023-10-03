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
#include "Values.hpp"
#include "World.hpp"
#include <SDL_stdinc.h>

SDLDisplayClass::SDLDisplayClass()
{
    const Uint32 windowFlags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    _window = SDL_CreateWindow("R-Type", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                               windowFlags);
    if (_window == nullptr) {
        std::cout << "Failed to open SDL window: " << SDL_GetError() << std::endl;
        return;
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return;
    }
}

size_t SDLDisplayClass::addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                  Component::LoadedSprite aSprite)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.getComponent<ECS::Utils::Vector2f>();
    auto &spd = world.getComponent<Component::Speed>();
    auto &type = world.getComponent<Component::TypeEntity>();
    auto &sprite = world.getComponent<Component::LoadedSprite>();
    const size_t idx = world.createEntity();

    vec.insertAt(idx, aPos);
    spd.insertAt(idx, aSpeed);
    type.insertAt(idx, aType);
    sprite.insertAt(idx, aSprite);
    return idx;
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
        delete sprite->rect;
        delete sprite->srcRect;
    }
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
