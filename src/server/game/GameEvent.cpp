#include "GameEvent.hpp"

namespace Game {

    GameEvent::GameEvent() : ECS::Event::Event(ECS::Event::EventType::GAME)
    {
    }

}
