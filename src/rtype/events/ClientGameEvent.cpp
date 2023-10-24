#include "ClientGameEvent.hpp"

namespace RType {

    ClientGameEvent::ClientGameEvent(ClientEventType aType)
        : _type(aType)
    {}

    ClientGameEvent::ClientGameEvent(ClientEventType aType, Network::IPayload *aPayload)
        : _type(aType),
          _payload(aPayload)
    {}

    ClientEventType ClientGameEvent::getType() const
    {
        return _type;
    }

} // namespace RType
