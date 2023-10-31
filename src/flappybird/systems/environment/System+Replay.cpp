#include "Components.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    static void setupEntities()
    {
        auto &world = ECS::Core::World::getInstance();

        try {
            // Get config
            auto &conf = ConfigReader::getInstance().loadConfig(CONFIG_PATH);
            auto &scoreConf = conf["entities"]["score"];
            auto &ground1Conf = conf["entities"]["ground_1"];
            auto &ground2Conf = conf["entities"]["ground_2"];
            auto &birdConf = conf["entities"]["bird"];
            auto &pipesConf = conf["entities"]["pipes"];
            auto &physicConf = ECS::Physic::PhysicPluginConfig::getInstance();

            // Get components
            auto &vec = world.getComponent<ECS::Utils::Vector2f>();
            auto &speed = world.getComponent<Component::Speed>();
            auto &type = world.getComponent<Component::TypeEntity>();
            auto &sprite = world.getComponent<Component::LoadedSprite>();
            auto &weight = world.getComponent<Component::Weight>();
            auto &jump = world.getComponent<Component::Jump>();
            auto &hitbox = world.getComponent<Component::HitBox>();
            auto &score = world.getComponent<Component::Score>();
            auto &text = world.getComponent<Component::TextComponent>();

            // Setup background
            size_t backgroundId = world.createEntity();
            vec.insertAt(backgroundId, ECS::Utils::Vector2f {0, 0});
            type.insertAt(backgroundId, Component::TypeEntity {EntityType::BACKGROUND});
            sprite.insertAt(backgroundId, Component::LoadedSprite {"config/flappybird/sprites/background.json"});

            // Setup score entity
            size_t scoreId = world.createEntity();
            vec.insertAt(scoreId, ECS::Utils::Vector2f {scoreConf["position"]["x"], scoreConf["position"]["y"]});
            type.insertAt(scoreId, Component::TypeEntity {EntityType::TEXT});
            score.insertAt(scoreId, Component::Score {0});
            text.insertAt(scoreId, Component::TextComponent("0", Component::TextColor::WHITE, scoreConf["size"]));

            // Setup pipes
            for (auto &pipe : pipesConf["items"]) {
                size_t pipeId = world.createEntity();
                std::string pipePath =
                    "config/flappybird/sprites/pipe-" + pipe["orientation"].get<std::string>() + ".json";
                float pipeScore = 2;

                if (pipe["scored"]) {
                    pipeScore = 0;
                }

                vec.insertAt(pipeId, ECS::Utils::Vector2f {pipe["x"], pipe["y"]});
                speed.insertAt(pipeId, Component::Speed {pipesConf["speed"]});
                type.insertAt(pipeId, Component::TypeEntity {EntityType::PIPE});
                sprite.insertAt(pipeId, Component::LoadedSprite {pipePath});
                hitbox.insertAt(pipeId,
                                Component::HitBox {pipesConf["hitbox"]["width"], pipesConf["hitbox"]["height"]});
                score.insertAt(pipeId, Component::Score {pipeScore});
            }

            // Setup ground entities
            size_t ground1Id = world.createEntity();
            vec.insertAt(ground1Id, ECS::Utils::Vector2f {0, ground1Conf["position"]["y"]});
            speed.insertAt(ground1Id, Component::Speed {ground1Conf["speed"]});
            type.insertAt(ground1Id, Component::TypeEntity {EntityType::GROUND});
            sprite.insertAt(ground1Id, Component::LoadedSprite {"config/flappybird/sprites/ground.json"});
            hitbox.insertAt(ground1Id,
                            Component::HitBox {ground1Conf["hitbox"]["width"], ground1Conf["hitbox"]["height"]});

            size_t ground2Id = world.createEntity();
            vec.insertAt(ground2Id, ECS::Utils::Vector2f {ground2Conf["position"]["x"], ground2Conf["position"]["y"]});
            speed.insertAt(ground2Id, Component::Speed {ground2Conf["speed"]});
            type.insertAt(ground2Id, Component::TypeEntity {EntityType::GROUND});
            sprite.insertAt(ground2Id, Component::LoadedSprite {"config/flappybird/sprites/ground.json"});
            hitbox.insertAt(ground2Id,
                            Component::HitBox {ground2Conf["hitbox"]["width"], ground2Conf["hitbox"]["height"]});

            // Setup player entity
            size_t birdId = world.createEntity();
            vec.insertAt(birdId, ECS::Utils::Vector2f {birdConf["position"]["x"], birdConf["position"]["y"]});
            type.insertAt(birdId, Component::TypeEntity {EntityType::BIRD});
            sprite.insertAt(birdId, Component::LoadedSprite {"config/flappybird/sprites/bird.json"});
            weight.insertAt(birdId, Component::Weight(birdConf["weight"], physicConf._initialJumpVelocity));
            jump.insertAt(birdId, Component::Jump(birdConf["jump"]["strength"], birdConf["jump"]["height"],
                                                  birdConf["jump"]["floating"]));
            hitbox.insertAt(birdId, Component::HitBox {birdConf["hitbox"]["width"], birdConf["hitbox"]["height"]});
        } catch (std::exception &e) {
            Logger::error("Failed to load config: " + std::string(e.what()));
        }
    }

    void System::replay()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &world = Core::World::getInstance();
        auto &events = eventManager->getEventsByType<Event::KeyboardEvent>();
        auto &type = world.getComponent<Component::TypeEntity>();

        size_t typeSize = type.size();

        // first setup
        if (typeSize < 1 || !type[1].has_value()) {
            setupEntities();
            return;
        }

        // detect ESCAPE key press
        for (auto &keyEvent : events) {
            if (keyEvent._keyId != Event::KeyIdentifier::ESCAPE) {
                continue;
            }
            // check player doesn't exist
            for (size_t i = 0; i < typeSize; i++) {
                if (!type[i].has_value() || type[i].value().type != EntityType::BIRD) {
                    continue;
                }
                return;
            }
            // kill all entities
            for (size_t i = 0; i < typeSize; i++) {
                world.killEntity(i);
            }
            return;
        }
    }
} // namespace ECS
