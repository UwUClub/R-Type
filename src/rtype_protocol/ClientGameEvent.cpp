#include "ClientGameEvent.hpp"

namespace RTypeProtocol {

    ClientGameEvent::ClientGameEvent(ClientEventType aType, size_t aId)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _id(aId)
    {}

    ClientGameEvent::ClientGameEvent(ClientEventType aType, size_t aId, std::vector<float> aPayload)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _id(aId),
          _payload(aPayload)
    {}

} // namespace RTypeProtocol
