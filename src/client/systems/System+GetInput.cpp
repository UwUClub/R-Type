#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include <unordered_map>
namespace ECS {
    void System::getInput()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN && (_keyMap.find(event.key.keysym.sym) != _keyMap.end())) {
                try {
                    auto *keyEvent =
                        new Event::KeyboardEvent(_keyMap.at(event.key.keysym.sym), Event::KeyState::PRESSED);
                    eventManager->pushEvent(keyEvent);
                } catch (std::exception &e) {
                    std::cerr << "LOL" << std::endl;
                    std::cerr << e.what() << std::endl;
                }
            }
            if (event.type == SDL_WINDOWEVENT && (_windowEventMap.find(event.window.event) != _windowEventMap.end())) {
                auto *windowEvent = new Event::WindowEvent(
                    SCREEN_WIDTH, SCREEN_WIDTH, 0, 0, ECS::Event::WindowDisplayState::FULLSCREEN,
                    ECS::Event::WindowFocusState::FOCUSED, _windowEventMap.at(event.window.event));
                eventManager->pushEvent(windowEvent);
            }
        }
    }
} // namespace ECS