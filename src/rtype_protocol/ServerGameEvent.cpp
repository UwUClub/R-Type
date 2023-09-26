#include "ServerGameEvent.hpp"

namespace RTypeProtocol {

    ServerGameEvent::ServerGameEvent(ServerEventType aType, size_t aId)
        : ECS::Event::Event(ECS::Event::EventType::GAME), _type(aType), _id(aId)
    {}

} // namespace RTypeProtocol
