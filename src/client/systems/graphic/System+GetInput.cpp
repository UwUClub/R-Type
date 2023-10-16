#include <functional>
#include "EventManager.hpp"
#include "Inputs.hpp"
#include "KeyboardEvent.hpp"
#include "RayDisplayClass.hpp"
#include "Raylib.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include <unordered_map>

namespace ECS {
    void System::getInput()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();

        if (Raylib::isKeyPressed(Raylib::KeyboardKey::KB_UP)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::UP, Event::KeyState::PRESSED));
        }

        if (Raylib::isKeyPressed(Raylib::KeyboardKey::KB_DOWN)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::DOWN, Event::KeyState::PRESSED));
        }

        if (Raylib::isKeyPressed(Raylib::KeyboardKey::KB_LEFT)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::LEFT, Event::KeyState::PRESSED));
        }

        if (Raylib::isKeyPressed(Raylib::KeyboardKey::KB_RIGHT)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::RIGHT, Event::KeyState::PRESSED));
        }

        if (Raylib::isKeyPressed(Raylib::KeyboardKey::KB_SPACE)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::SPACE, Event::KeyState::PRESSED));
        }

        if (WindowShouldClose()) {
            Core::World::getInstance().stop();
        }
    } // namespace ECS
} // namespace ECS
