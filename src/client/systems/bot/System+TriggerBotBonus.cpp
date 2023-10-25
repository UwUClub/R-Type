#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotBonus(Core::SparseArray<Component::Speed> &aSpeed,
                                 Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        auto &typeUtils = RType::TypeUtils::getInstance();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (unsigned short i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_BONUS) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerGotBonusPayload>();

            unsigned short const localBotId = typeUtils.getEntityIdByOnlineId(aType, payload.playerId);

            if (payload.bonusId == 1) {
                if (!aSpeed[localBotId].has_value()) {
                    toRemove.push_back(i);
                    continue;
                }
                aSpeed[localBotId].value().speed += (10.F);
            }
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }
} // namespace ECS
