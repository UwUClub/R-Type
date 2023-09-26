#include "ClientGameEvent.hpp"

namespace RTypeProtocol {

    ClientGameEvent::ClientGameEvent(ClientEventType aType, size_t aId)
        : ECS::Event::Event(ECS::Event::EventType::GAME), _type(aType), _id(aId)
    {}

} // namespace RTypeProtocol
