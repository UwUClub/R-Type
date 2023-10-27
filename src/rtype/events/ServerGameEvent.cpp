#include "ServerGameEvent.hpp"
#include <boost/asio.hpp>

namespace RType {

    using boost::asio::ip::udp;

    ServerGameEvent::ServerGameEvent(ServerEventType aType, unsigned short aEntityId, Network::IPayload *aPayload)
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
