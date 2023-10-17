#include "ConfigReader.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::jump(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Jump> &aJump,
                      Core::SparseArray<Component::Weight> &aWeight)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        auto &world = Core::World::getInstance();
        auto &birdConf = ConfigReader::getInstance().get()["entities"]["bird"];

        for (size_t i = 0; i < aJump.size(); i++) {
            if (aJump[i].value().isJumping) {
                float targetY = aJump[i].value().initialAltitude - aJump[i].value().height;
                auto endTolerance = static_cast<float>(birdConf["jump"]["floating"]);

                if (std::abs(targetY - aPos[i].value().y) < endTolerance) {
                    aJump[i].value().isJumping = false;
                } else {
                    aPos[i].value().y +=
                        (targetY - aPos[i].value().y) * aJump[i].value().strength * world.getDeltaTime();
                }

                if (aWeight[i].has_value()) {
                    aWeight[i].value().resetFallVelocity();
                }
            }

            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent *>(event);
                if (keyEvent->_keyId == Event::KeyIdentifier::SPACE) {
                    aJump[i].value().isJumping = true;
                    aJump[i].value().initialAltitude = aPos[i].value().y;
                }
            }
        }
    }
} // namespace ECS