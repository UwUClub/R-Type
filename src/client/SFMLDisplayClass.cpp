/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#include "SFMLDisplayClass.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include "EwECS/SparseArray.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "LoadedSprite.hpp"
#include "Values.hpp"
#if defined(__linux__)
    #include <libgen.h>
    #include <limits.h>
    #include <unistd.h>
#endif

SFMLDisplayClass::SFMLDisplayClass()
{
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "R-Type");
    /*if (_window == nullptr) {
        std::cout << "Failed to create SFML window: " << std::endl;
        return;
    }*/
#if defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count < 0 || count >= PATH_MAX) {
        _assetPath = "./";
        return;
    }
    result[count] = '\0';
    char *dir = dirname(result);
    if (dir == nullptr) {
        _assetPath = "./";
        return;
    }
    _assetPath = std::string(dir) + "/";
#else
    _assetPath = "./";
#endif
}

size_t SFMLDisplayClass::addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
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

sf::Texture *SFMLDisplayClass::getTexture(const std::string &aPath)
{
    std::string path = _assetPath + aPath;
    auto *texture = new sf::Texture();

    if (_textures.find(path) == _textures.end()) {
        if (texture->loadFromFile(path.c_str())) {
            _textures[path] = texture;
        }
        if (_textures[path] == nullptr) {
            std::cerr << "Failed to create texture" << std::endl;
            delete texture;
            return nullptr;
        }
    }
    return _textures[path];
}

void SFMLDisplayClass::freeRects(const std::size_t &aIdx)
{
    auto &world = ECS::Core::World::getInstance();
    auto &sprites = world.getComponent<Component::LoadedSprite>();

    if (!sprites[aIdx].has_value()) {
        return;
    }
    delete sprites[aIdx]->rect;
    delete sprites[aIdx]->srcRect;
}

SFMLDisplayClass::~SFMLDisplayClass()
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
        delete texture.second;
    }
    _window.close();
}
