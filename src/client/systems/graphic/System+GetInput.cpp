#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include "raylib.h"
#include <unordered_map>

namespace ECS {
    void System::getInput()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();

        if (IsKeyPressed(KEY_UP)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::UP, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_DOWN)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::DOWN, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_LEFT)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::LEFT, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::RIGHT, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_SPACE)) {
            eventManager->pushEvent<Event::KeyboardEvent>(
                Event::KeyboardEvent(Event::KeyIdentifier::SPACE, Event::KeyState::PRESSED));
        }

        if (WindowShouldClose()) {
            Core::World::getInstance().stop();
        }
    } // namespace ECS
} // namespace ECS
