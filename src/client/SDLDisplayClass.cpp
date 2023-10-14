/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#include "SDLDisplayClass.hpp"
#include <algorithm>
#include "IsAlive.hpp"
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
                                  Component::LoadedSprite aSprite, Component::HitBox aHitBox,
                                  Component::IsAlive aIsAlive)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.getComponent<ECS::Utils::Vector2f>();
    auto &spd = world.getComponent<Component::Speed>();
    auto &type = world.getComponent<Component::TypeEntity>();
    auto &sprite = world.getComponent<Component::LoadedSprite>();
    auto &hitbox = world.getComponent<Component::HitBox>();
    auto &isAlive = world.getComponent<Component::IsAlive>();
    const size_t idx = world.createEntity();

    vec.insertAt(idx, aPos);
    spd.insertAt(idx, aSpeed);
    type.insertAt(idx, aType);
    sprite.insertAt(idx, aSprite);
    hitbox.insertAt(idx, aHitBox);
    isAlive.insertAt(idx, aIsAlive);
    return idx;
}

SDL_Texture *SDLDisplayClass::getTexture(const std::string &aPath)
{
    if (_textures.find(aPath) == _textures.end()) {
        _textures[aPath] = IMG_LoadTexture(_renderer, aPath.c_str());
        if (_textures[aPath] == nullptr) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            return nullptr;
        }
    }
    return _textures[aPath];
}

void SDLDisplayClass::freeRects(const std::size_t &aIdx)
{
    auto &world = ECS::Core::World::getInstance();
    auto &sprites = world.getComponent<Component::LoadedSprite>();

    if (!sprites[aIdx].has_value()) {
        return;
    }
    delete sprites[aIdx]->rect;
    delete sprites[aIdx]->srcRect;
}

SDLDisplayClass::~SDLDisplayClass()
{
    auto &world = ECS::Core::World::getInstance();
    auto &sprites = world.getComponent<Component::LoadedSprite>();

    for (auto &sprite : sprites) {
        if (!sprite.has_value()) {
            continue;
        }
        delete sprite->rect;
        delete sprite->srcRect;
    }
    for (auto &texture : _textures) {
        SDL_DestroyTexture(texture.second);
    }
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
