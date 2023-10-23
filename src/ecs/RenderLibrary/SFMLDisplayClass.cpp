/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#include "SFMLDisplayClass.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "LoadedSprite.hpp"
#include "World.hpp"
#if defined(__linux__)
    #include <libgen.h>
    #include <limits.h>
    #include <unistd.h>
#endif

SFMLDisplayClass::SFMLDisplayClass()
{
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
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

void SFMLDisplayClass::getInput()
{
    Event::EventManager *eventManager = Event::EventManager::getInstance();
    SFMLDisplayClass *display = &SFMLDisplayClass::getInstance();
    sf::Event event;

    while (display->_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed && (_keyMap.find(event.key.code) != _keyMap.end())) {
            try {
                auto *keyEvent = new Event::KeyboardEvent(_keyMap.at(event.key.code), Event::KeyState::PRESSED);
                eventManager->pushEvent(keyEvent);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (event.type == sf::Event::Closed) {
            display->_window.close();
            Core::World::getInstance().stop();
        }
    }
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
