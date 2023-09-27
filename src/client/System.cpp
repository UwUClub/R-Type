#include "System.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <functional>

namespace ECS {
    void System::movePlayer(Core::World &world, Core::SparseArray<Utils::Vector2f> &aPos,
                            Core::SparseArray<Utils::Speed> &aSpeed,
                            Core::SparseArray<Utils::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<const Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &)>> keyMap = {
            {Event::KeyIdentifier::UP, [](float &spd, Utils::Vector2f &xy) { xy.y = xy.y <= 0 ? 0 : xy.y -= spd; }},
            {Event::KeyIdentifier::DOWN, [](float &spd, Utils::Vector2f &xy) { xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd; }},
            {Event::KeyIdentifier::LEFT, [](float &spd, Utils::Vector2f &xy) { xy.x = xy.x <= 0 ? 0 : xy.x -= spd; }},
            {Event::KeyIdentifier::RIGHT, [](float &spd, Utils::Vector2f &xy) { xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd; }},
        };

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent *>(event);
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, aPos[i].value());
            }
        }
    }

    void System::getInput(Core::World &aWorld)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && (_keyMap.find(event.key.keysym.sym) != _keyMap.end())) {
                auto keyEvent = new Event::KeyboardEvent(_keyMap.at(event.key.keysym.sym), Event::KeyState::PRESSED);
                eventManager->pushEvent(keyEvent);
            }
            if (event.type == SDL_WINDOWEVENT && (_windowEventMap.find(event.window.event) != _windowEventMap.end())) {
                auto windowEvent = new Event::WindowEvent(1920, 1920, 0, 0, ECS::Event::WindowDisplayState::FULLSCREEN,
                                                          ECS::Event::WindowFocusState::FOCUSED,
                                                          _windowEventMap.at(event.window.event));
                eventManager->pushEvent(windowEvent);
            }
        }
    }

    void System::quitSDL(Core::World &aWorld)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto windowEvent = eventManager->getEventsByType(Event::EventType::WINDOW);
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        for (size_t i = 0; i < windowEvent.size(); i++) {
            auto event = static_cast<Event::WindowEvent *>(windowEvent[i]);
            if (event->_windowEventType == Event::WindowEventType::CLOSED) {
                display.~SDLDisplayClass();
                break;
            }
        }
    }

    void System::loadTextures(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i].value().texture != nullptr)
                continue;
            aSprites[i].value().texture = IMG_LoadTexture(display._renderer, aSprites[i].value().path.c_str());
            if (aSprites[i].value().texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprites[i].value().path << std::endl;
            }
        }
    }

    void System::displayEntities(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        SDL_SetRenderDrawColor(display._renderer, 0, 0, 0, 255);
        SDL_RenderClear(display._renderer);
        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i].value().texture == nullptr)
                continue;
            aSprites[i].value().srcRect.x = aPos[i].value().x;
            aSprites[i].value().srcRect.y = aPos[i].value().y;
            SDL_RenderCopy(display._renderer, aSprites[i].value().texture, &aSprites[i].value().rect,
                           &aSprites[i].value().srcRect);
        }
    }

} // namespace ECS