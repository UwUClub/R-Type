#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/World.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::jump(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Jump> &aJump,
                      Core::SparseArray<Component::Weight> &aWeight)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<Event::KeyboardEvent>();
        auto &world = Core::World::getInstance();
        auto &birdConf = ConfigReader::getInstance().get(CONFIG_PATH)["entities"]["bird"];
        const auto &size = aJump.size();

        for (size_t i = 0; i < size; i++) {
            if (!aPos[i].has_value() || !aJump[i].has_value()) {
                continue;
            }
            auto &pos = aPos[i].value();
            auto &jump = aJump[i].value();
            if (jump.isJumping) {
                float targetY = jump.initialAltitude - jump.height;
                auto endTolerance = static_cast<float>(birdConf["jump"]["floating"]);

                if (std::abs(targetY - pos.y) < endTolerance) {
                    jump.isJumping = false;
                } else {
                    pos.y += (targetY - pos.y) * jump.strength * world.getDeltaTime();
                }

                if (aWeight[i].has_value()) {
                    aWeight[i].value().resetFallVelocity();
                }
            }

            for (auto &keyEvent : events) {
                if (keyEvent._keyId == Event::KeyIdentifier::SPACE) {
                    jump.isJumping = true;
                    jump.initialAltitude = pos.y;
                }
            }
        }
    }
} // namespace ECS
