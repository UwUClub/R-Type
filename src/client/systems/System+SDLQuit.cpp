#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "WindowEvent.hpp"

void ECS::System::quitSDL(Core::World &aWorld)
{
    Event::EventManager *eventManager = Event::EventManager::getInstance();
    auto windowEvent = eventManager->getEventsByType(Event::EventType::WINDOW);
    SDLDisplayClass &display = SDLDisplayClass::getInstance();

    for (size_t i = 0; i < windowEvent.size(); i++) {
        auto event = static_cast<Event::WindowEvent *>(windowEvent[i]);
        if (event->_windowEventType == Event::WindowEventType::CLOSED) {
            display.~SDLDisplayClass();
            aWorld.stop();
            break;
        }
    }
}