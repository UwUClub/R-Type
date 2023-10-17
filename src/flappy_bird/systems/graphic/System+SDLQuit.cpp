#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "WindowEvent.hpp"

void ECS::System::quitSDL()
{
    auto &world = ECS::Core::World::getInstance();
    Event::EventManager *eventManager = Event::EventManager::getInstance();
    auto windowEvent = eventManager->getEventsByType(Event::EventType::WINDOW);

    for (auto &idx : windowEvent) {
        auto *event = static_cast<Event::WindowEvent *>(idx);
        if (event->_windowEventType == Event::WindowEventType::CLOSED) {
            world.stop();
            break;
        }
    }
}
