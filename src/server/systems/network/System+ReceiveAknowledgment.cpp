#include <cstddef>
#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"

namespace ECS {
    void System::receiveAknowledgment(RType::ServerGameEvent *aEvent)
    {
        auto &world = ECS::Core::World::getInstance();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::AKNOWLEDGMENT) {
            size_t playerId = aEvent->getEntityId();

            if (connectionComp[playerId].has_value()) {
                connectionComp[playerId].value().status = Network::ConnectionStatus::CONNECTED;
                connectionComp[playerId].value().age = 0;
            }
        }
    }
} // namespace ECS
