#include "ServerGameEvent.hpp"
#include <boost/asio.hpp>

namespace RType {

    using boost::asio::ip::udp;

    ServerGameEvent::ServerGameEvent(ServerEventType aType, int aEntityId, const std::vector<float> &aPayload,
                                     udp::endpoint aClientEndpoint)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _entityId(aEntityId),
          _payload(aPayload),
          _clientEndpoint(aClientEndpoint)
    {}

    ServerEventType ServerGameEvent::getType() const
    {
        return _type;
    }

    int ServerGameEvent::getEntityId() const
    {
        return _entityId;
    }

    const std::vector<float> &ServerGameEvent::getPayload() const
    {
        return _payload;
    }

    udp::endpoint ServerGameEvent::getClientEndpoint() const
    {
        return _clientEndpoint;
    }

} // namespace RType
