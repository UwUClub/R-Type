#include <functional>
#include "Event.hpp"
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
            eventManager->pushEvent(new Event::KeyboardEvent(Event::KeyIdentifier::UP, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_DOWN)) {
            eventManager->pushEvent(new Event::KeyboardEvent(Event::KeyIdentifier::DOWN, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_LEFT)) {
            eventManager->pushEvent(new Event::KeyboardEvent(Event::KeyIdentifier::LEFT, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            eventManager->pushEvent(new Event::KeyboardEvent(Event::KeyIdentifier::RIGHT, Event::KeyState::PRESSED));
        }

        if (IsKeyPressed(KEY_SPACE)) {
            eventManager->pushEvent(new Event::KeyboardEvent(Event::KeyIdentifier::SPACE, Event::KeyState::PRESSED));
        }

        if (WindowShouldClose()) {
            Core::World::getInstance().stop();
        }
    } // namespace ECS
} // namespace ECS
