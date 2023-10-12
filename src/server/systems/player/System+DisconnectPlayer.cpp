#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::disconnectPlayer(RType::ServerGameEvent *aEvent)
    {
        Core::World &world = Core::World::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::DISCONNECT) {
            size_t playerId = aEvent->getEntityId();

            world.killEntity(playerId);
            server.removeClient(playerId);

            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_DISCONNECTION),
                             {static_cast<float>(playerId)}, connectionComp);
        }
    }
} // namespace ECS
