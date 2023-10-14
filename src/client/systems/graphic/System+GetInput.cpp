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
            eventManager->pushEvent("UP", Event::EventType::KEYBOARD);
        }

        if (IsKeyPressed(KEY_DOWN)) {
            eventManager->pushEvent("DOWN", Event::EventType::KEYBOARD);
        }

        if (IsKeyPressed(KEY_LEFT)) {
            eventManager->pushEvent("LEFT", Event::EventType::KEYBOARD);
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            eventManager->pushEvent("RIGHT", Event::EventType::KEYBOARD);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            eventManager->pushEvent("SPACE", Event::EventType::KEYBOARD);
        }

        if (WindowShouldClose()) {
            Core::World::getInstance().stop();
        }
    } // namespace ECS
} // namespace ECS
