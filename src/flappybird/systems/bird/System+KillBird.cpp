#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "components/Speed.hpp"
#include "components/TypeEntity.hpp"

namespace ECS {

    void System::killBird()
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        auto &vec = world.getComponent<ECS::Utils::Vector2f>();
        auto &hitbox = world.getComponent<Component::HitBox>();
        auto &type = world.getComponent<Component::TypeEntity>();
        auto &speed = world.getComponent<Component::Speed>();
        auto &text = world.getComponent<Component::TextComponent>();
        size_t typeSize = type.size();

        // Get info message conf
        auto &configReader = ConfigReader::ConfigReader::getInstance();
        auto &conf = configReader.loadConfig(CONFIG_PATH);
        auto &replayMessageConf = conf["entities"]["replay_message"];

        for (size_t birdId = 0; birdId < typeSize; birdId++) {
            if (!type[birdId].has_value() || type[birdId].value().type != EntityType::BIRD
                || !hitbox[birdId].has_value() || !hitbox[birdId].value().isColliding) {
                continue;
            }
            auto &colliders = hitbox[birdId].value().collidingId;
            for (auto &collider : colliders) {
                if (!type[collider].has_value()) {
                    continue;
                }
                auto &colliderType = type[collider].value().type;
                if (colliderType != EntityType::GROUND && colliderType != EntityType::PIPE) {
                    continue;
                }
                world.killEntity(birdId);

                // Stop moving entities
                for (size_t i = 0; i < typeSize; i++) {
                    if (!speed[i].has_value()) {
                        continue;
                    }
                    speed[i].value().speed = 0;
                }

                // Add info message
                auto replayMessageId = world.createEntity();
                vec.insertAt(replayMessageId, ECS::Utils::Vector2f {replayMessageConf["position"]["x"],
                                                                    replayMessageConf["position"]["y"]});
                text.insertAt(replayMessageId,
                              Component::TextComponent("Press ENTER to play again", Component::TextColor::WHITE,
                                                       replayMessageConf["size"]));
                return;
            }
        }
    }
} // namespace ECS
