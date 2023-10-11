#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "WindowEvent.hpp"

void ECS::System::quitSDL(Event::WindowEvent *aEvent)
{
    auto &world = ECS::Core::World::getInstance();

    if (aEvent->_windowEventType == Event::WindowEventType::CLOSED) {
        world.stop();
    }
}
