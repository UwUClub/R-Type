#include <cstddef>
#include <iostream>
#include "Components.hpp"
#include "EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::handlePlayerCrash(Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::Connection> &aConnection)
    {
        Core::World &world = Core::World::getInstance();

        for (int i = 0; i < aConnection.size(); i++) {
            if (aType[i].has_value() && aType[i]->isPlayer && aConnection[i].has_value() && aIsAlive[i].has_value()
                && aConnection[i].value().status == Network::ConnectionStatus::PENDING) {
                aConnection[i].value().age += world.getDeltaTime();
                if (aConnection[i].value().age >= PACKET_TIMEOUT) {
                    std::cout << "Player " << i << " timed out" << std::endl;
                    aIsAlive[i].value().isAlive = false;
                }
            }
        }
    }
} // namespace ECS
