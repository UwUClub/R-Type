#include <cstddef>
#include <iostream>
#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::handlePlayerCrash(Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::Connection> &aConnection)
    {
        Core::World &world = Core::World::getInstance();
        const auto size = aConnection.size();

        for (size_t i = 0; i < size; i++) {
            if (aType[i].has_value() && aType[i]->isPlayer && aConnection[i].has_value() && aIsAlive[i].has_value()
                && aConnection[i].value().status == Network::ConnectionStatus::PENDING) {
                aConnection[i].value().age += world.getDeltaTime();
                if (aConnection[i].value().age >= PACKET_TIMEOUT) {
                    std::cout << "Player " << i << " crashed" << std::endl;
                    aIsAlive[i].value().isAlive = false;
                }
            }
        }
    }
} // namespace ECS
