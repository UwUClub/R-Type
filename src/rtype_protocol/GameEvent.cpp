#include "GameEvent.hpp"

namespace RTypeProtocol {

    GameEvent::GameEvent()
        : ECS::Event::Event(ECS::Event::EventType::GAME)
    {}

} // namespace Game
