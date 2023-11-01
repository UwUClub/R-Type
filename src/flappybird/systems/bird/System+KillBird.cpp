#include <exception>
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Music/Music.hpp"
#include "EwECS/Music/MusicComponent.hpp"
#include "EwECS/Music/MusicPlugin.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "EwECS/Sound/Sound.hpp"
#include "EwECS/Sound/SoundComponent.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "components/Speed.hpp"
#include "components/TypeEntity.hpp"

namespace ECS {

    static void killPlayer(size_t aBirdId)
    {
        try {
            ECS::Core::World &world = ECS::Core::World::getInstance();
            auto &vec = world.getComponent<ECS::Utils::Vector2f>();
            auto &type = world.getComponent<Component::TypeEntity>();
            auto &speed = world.getComponent<Component::Speed>();
            auto &text = world.getComponent<Component::TextComponent>();
            auto &music = world.getComponent<Component::MusicComponent>();

            auto &replayMessageConf = ConfigReader::getInstance().get(CONFIG_PATH)["entities"]["replay_message"];
            auto &soundsConf = ConfigReader::getInstance().get(CONFIG_PATH)["sounds"];

            size_t typeSize = type.size();

            // Remove music
            ECS::Music::stop(music[aBirdId].value());
            world.removeEntityInComponent<Component::MusicComponent>(aBirdId);
            world.killEntity(aBirdId);

            // Stop moving entities
            for (size_t i = 0; i < typeSize; i++) {
                if (!speed[i].has_value()) {
                    continue;
                }
                speed[i].value().speed = 0;
            }

            // Add info message
            auto replayMessageId = world.createEntity();
            vec.insertAt(replayMessageId,
                         ECS::Utils::Vector2f {replayMessageConf["position"]["x"], replayMessageConf["position"]["y"]});
            type.insertAt(replayMessageId, Component::TypeEntity {EntityType::TEXT});
            text.insertAt(replayMessageId,
                          Component::TextComponent(replayMessageConf["text"], Component::TextColor::WHITE,
                                                   replayMessageConf["size"]));

            // Add death sound
            world.emplaceEntityComponent<Component::SoundComponent>(replayMessageId, soundsConf["death"]["path"],
                                                                    soundsConf["death"]["volume"],
                                                                    soundsConf["death"]["loop"]);
        } catch (std::exception &e) {
            Logger::error("Failed to load config: " + std::string(e.what()));
        }
    }

    void System::killBird()
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        auto &vec = world.getComponent<ECS::Utils::Vector2f>();
        auto &hitbox = world.getComponent<Component::HitBox>();
        auto &type = world.getComponent<Component::TypeEntity>();
        size_t typeSize = type.size();

        try {
            auto &birdConf = ConfigReader::getInstance().get(CONFIG_PATH)["entities"]["bird"];

            for (size_t birdId = 0; birdId < typeSize; birdId++) {
                if (!type[birdId].has_value() || type[birdId].value().type != EntityType::BIRD
                    || !hitbox[birdId].has_value() || !vec[birdId].has_value()) {
                    continue;
                }

                // Check bird too high
                float birdHeight = birdConf["hitbox"]["height"];
                if (vec[birdId].value().y <= -birdHeight) {
                    killPlayer(birdId);
                    return;
                }

                if (!hitbox[birdId].value().isColliding) {
                    continue;
                }

                // Check collision with pipe or ground
                auto &colliders = hitbox[birdId].value().collidingId;
                for (auto &collider : colliders) {
                    if (!type[collider].has_value()) {
                        continue;
                    }
                    auto &colliderType = type[collider].value().type;
                    if (colliderType != EntityType::GROUND && colliderType != EntityType::PIPE) {
                        continue;
                    }
                    killPlayer(birdId);
                    return;
                }
            }
        } catch (std::exception &e) {
            Logger::error("Failed to load config: " + std::string(e.what()));
        }
    }
} // namespace ECS
