#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include <unordered_map>

namespace ECS {
    void System::getInput()
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
} // namespace ECS
