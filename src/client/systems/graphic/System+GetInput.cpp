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

        for (const auto &itx : _keyMap) {
            if (IsKeyDown(itx.first)) {
                try {
                    auto *keyEvent = new Event::KeyboardEvent(itx.second, Event::KeyState::PRESSED);
                    eventManager->pushEvent(keyEvent);
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            } else if (IsKeyUp(itx.first)) {
                try {
                    auto *keyEvent = new Event::KeyboardEvent(itx.second, Event::KeyState::RELEASED);
                    eventManager->pushEvent(keyEvent);
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        if (WindowShouldClose()) {
            Core::World::getInstance().stop();
        }
    } // namespace ECS
} // namespace ECS
