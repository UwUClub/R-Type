#include "ServerGameEvent.hpp"

namespace RType {

    ServerGameEvent::ServerGameEvent(ServerEventType aType, unsigned short aEntityId, ECS::Network::IPayload *aPayload)
        : _type(aType),
          _entityId(aEntityId),
          _payload(aPayload)
    {}

    ServerEventType ServerGameEvent::getType() const
    {
        return _type;
    }

    unsigned short ServerGameEvent::getEntityId() const
    {
        return _entityId;
    }

} // namespace RType
