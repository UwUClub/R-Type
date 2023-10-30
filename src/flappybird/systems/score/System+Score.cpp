//
// Created by beafowl on 27/10/23.
//

#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::displayScore(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto &world = Core::World::getInstance();
        auto &type = world.getComponent<Component::TypeEntity>();
        auto &text = world.getComponent<Component::TextComponent>();

        // Setup score entity
        size_t scoreId = world.createEntity();
        type.insertAt(scoreId, Component::TypeEntity {EntityType::TEXT});
        text.insertAt(scoreId, Component::TextComponent {});

        ConfigReader &configReader = ConfigReader::getInstance();
        auto &conf = configReader.loadConfig(CONFIG_PATH);

        int score = 0;
        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aPos[i].has_value() || !aType[i].has_value() || aType[i].value().type != EntityType::BIRD) {
                continue;
            }
            auto &pos = aPos[i].value();
        }
        auto width = conf["graphics"]["width"].get<int>();
        text[scoreId]->text.setCharacterSize(50);
        text[scoreId]->text.setFillColor(sf::Color::White);
        text[scoreId]->text.setPosition(width / 2, 20);
        text[scoreId]->text.setString(std::to_string(score));
    }
} // namespace ECS