#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "IsAlive.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"
#include "Values.hpp"

namespace ECS {
    void System::triggerBonus(Core::SparseArray<Component::Speed> &aSpeed,
                              Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_BONUS) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerGotBonusPayload>();

            auto localPlayerId = RType::TypeUtils::getEntityIdByOnlineId(aType, payload.playerId);

            if (!aSpeed[localPlayerId].has_value()) {
                continue;
            }

            aSpeed[localPlayerId].value().speed *= BONUS_GAIN_FACTOR;

            auto localBonusId = RType::TypeUtils::getEntityIdByOnlineId(aType, payload.bonusId);

            world.killEntity(localBonusId);

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS