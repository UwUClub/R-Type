#include "System.hpp"
#include <SDL.h>
#include <cmath>
#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include <SDL_image.h>
#include <unordered_map>

namespace ECS {
    void System::applyGravity(Core::World &aWorld, Core::SparseArray<Utils::Vector2f> &aPos,
                              Core::SparseArray<Utils::Weight> &aWeight, Core::SparseArray<Utils::TypeEntity> &aType)
    {
        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            aPos[i].value().y += aWeight[i].value().weight * aWorld.getDeltaTime();
        }
    }

    void System::jump(Core::World &aWorld, Core::SparseArray<Utils::Vector2f> &aPos,
                      Core::SparseArray<Utils::Jump> &aJump, Core::SparseArray<Utils::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);

        for (size_t i = 0; i < aJump.size(); i++) {
            if (aJump[i].value().isJumping) {
                float targetY = aJump[i].value().initialAltitude - aJump[i].value().height;
                float endTolerance = aJump[i].value().height / 4.25f;

                if (std::abs(targetY - aPos[i].value().y) < endTolerance) {
                    aJump[i].value().isJumping = false;
                } else {
                    aPos[i].value().y +=
                        (targetY - aPos[i].value().y) * aJump[i].value().strength * aWorld.getDeltaTime();
                }
            }

            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent *>(event);
                if (keyEvent->_keyId == Event::KeyIdentifier::SPACE) {
                    aJump[i].value().isJumping = true;
                    aJump[i].value().initialAltitude = aPos[i].value().y;
                }
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
                auto windowEvent = new Event::WindowEvent(
                    SCREEN_WIDTH, SCREEN_WIDTH, 0, 0, ECS::Event::WindowDisplayState::FULLSCREEN,
                    ECS::Event::WindowFocusState::FOCUSED, _windowEventMap.at(event.window.event));
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