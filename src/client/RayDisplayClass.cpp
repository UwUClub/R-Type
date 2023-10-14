/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RayDisplayClass
*/

#include "RayDisplayClass.hpp"
#include <algorithm>
#include "IsAlive.hpp"
#include "SparseArray.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "World.hpp"
#include "raylib.h"
#if defined(__linux__)
    #include <libgen.h>
    #include <limits.h>
    #include <unistd.h>
#endif

RayDisplayClass::RayDisplayClass()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "R-Type");

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
    _assetPath = "./"
#endif
}

size_t RayDisplayClass::addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
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
    sprite.insertAt(idx, std::move(aSprite));
    hitbox.insertAt(idx, aHitBox);
    isAlive.insertAt(idx, aIsAlive);
    return idx;
}

Texture2D *RayDisplayClass::getTexture(const std::string &aPath)
{
    std::string path = _assetPath + aPath;

    if (_textures.find(path) == _textures.end()) {
        _textures[path] = LoadTexture(path.c_str());
    }
    return &_textures[path];
}

RayDisplayClass::~RayDisplayClass()
{
    auto &world = ECS::Core::World::getInstance();
    auto &sprites = world.getComponent<Component::LoadedSprite>();

    for (auto &sprite : sprites) {
        if (!sprite.has_value()) {
            continue;
        }
    }
    for (auto &texture : _textures) {
        UnloadTexture(texture.second);
    }
    CloseWindow();
}
