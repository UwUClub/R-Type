#include "ClientGameEvent.hpp"

namespace RType {

    ClientGameEvent::ClientGameEvent(ClientEventType aType)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType)
    {}

    ClientGameEvent::ClientGameEvent(ClientEventType aType, std::vector<float> aPayload)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _payload(aPayload)
    {}

    ClientEventType ClientGameEvent::getType() const
    {
        return _type;
    }

    std::vector<float> ClientGameEvent::getPayload() const
    {
        return _payload;
    }

} // namespace RType
