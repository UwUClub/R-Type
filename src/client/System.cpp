#include <SDL2/SDL.h>
#include "System.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"

namespace ECS {
    void System::movePlayer(Core::World &world, Core::SparseArray<ECS::Utils::Vector2f> &pos,
                            Core::SparseArray<ECS::Utils::Speed> &speed,
                            Core::SparseArray<ECS::Utils::TypeEntity> &type)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);

        for (size_t i = 0; i < pos.size(); i++) {
            if (!type[i].has_value() || !type[i].value().isPlayer) {
                continue;
            }
            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent *>(event);
                std::cout << "OUI " << (int)keyEvent->_keyId << std::endl;
                if (keyEvent->_keyId == Event::KeyIdentifier::UP)
                    pos[i].value().y -= speed[i].value().speed;
                if (keyEvent->_keyId == Event::KeyIdentifier::DOWN)
                    pos[i].value().y += speed[i].value().speed;
                if (keyEvent->_keyId == Event::KeyIdentifier::LEFT)
                    pos[i].value().x -= speed[i].value().speed;
                if (keyEvent->_keyId == Event::KeyIdentifier::RIGHT)
                    pos[i].value().x += speed[i].value().speed;
            }
        }
    }

    void System::getInput(Core::World &world)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && (_keyMap.find(event.key.keysym.sym) != _keyMap.end())) {
                auto keyEvent = new Event::KeyboardEvent(_keyMap.at(event.key.keysym.sym), Event::KeyState::PRESSED);
                eventManager->pushEvent(keyEvent);
            }
            if (event.type == SDL_WINDOWEVENT && (_windowEventMap.find(event.window.event) != _windowEventMap.end())) {
                auto windowEvent = new Event::WindowEvent(1920, 1920, 0, 0,
                                                          ECS::Event::WindowDisplayState::FULLSCREEN,
                                                          ECS::Event::WindowFocusState::FOCUSED,
                                                          _windowEventMap.at(event.window.event));
                eventManager->pushEvent(windowEvent);
            }
        }
    }

    void System::quitSDL(Core::World &world)
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

} // namespace ECS