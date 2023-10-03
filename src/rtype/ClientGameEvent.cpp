#include "ClientGameEvent.hpp"

namespace RTypeProtocol {

    ClientGameEvent::ClientGameEvent(ClientEventType aType, size_t aOnlineEntityId)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _onlineEntityId(aOnlineEntityId)
    {}

    ClientGameEvent::ClientGameEvent(ClientEventType aType, size_t aOnlineEntityId, std::vector<float> aPayload)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _onlineEntityId(aOnlineEntityId),
          _payload(aPayload)
    {}

    ClientEventType ClientGameEvent::getType() const
    {
        return _type;
    }

    std::size_t ClientGameEvent::getOnlineEntityId() const
    {
        return _onlineEntityId;
    }

    std::vector<float> ClientGameEvent::getPayload() const
    {
        return _payload;
    }

} // namespace RTypeProtocol
