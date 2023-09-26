#include "GameEvent.hpp"

namespace RTypeProtocol {

    GameEvent::GameEvent(ClientEvent aValue)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _value(aValue)
    {}

} // namespace RTypeProtocol
