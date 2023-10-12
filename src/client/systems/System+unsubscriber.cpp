#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::unsubscriber(RType::ClientGameEvent *aEvent)
    {
        if (aEvent->getType() == RType::ClientEventType::PLAYER_SPAWN) {
            Event::EventManager::getInstance()->unsubscribe<RType::ClientGameEvent>(ECS::System::createBackground);
        }
    }
} // namespace ECS
