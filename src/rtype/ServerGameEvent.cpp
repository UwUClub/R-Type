#include "ServerGameEvent.hpp"
#include <boost/asio.hpp>

namespace RTypeProtocol {

    using boost::asio::ip::udp;

    ServerGameEvent::ServerGameEvent(ServerEventType aType, size_t aEntityId, udp::endpoint aClientEndpoint)
        : ECS::Event::Event(ECS::Event::EventType::GAME),
          _type(aType),
          _entityId(aEntityId),
          _clientEndpoint(aClientEndpoint)
    {}

    ServerEventType ServerGameEvent::getType() const
    {
        return _type;
    }

    std::size_t ServerGameEvent::getEntityId() const
    {
        return _entityId;
    }

    udp::endpoint ServerGameEvent::getClientEndpoint() const
    {
        return _clientEndpoint;
    }

} // namespace RTypeProtocol
