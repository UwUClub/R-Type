#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/TextComponent.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::updateScore()
    {
        auto &world = Core::World::getInstance();
        auto &type = world.getComponent<Component::TypeEntity>();
        auto &text = world.getComponent<Component::TextComponent>();
        auto &score = world.getComponent<Component::Score>();
        auto &pos = world.getComponent<ECS::Utils::Vector2f>();

        try {
            auto &configReader = ConfigReader::getInstance();
            auto &conf = configReader.loadConfig(CONFIG_PATH);
            auto &birdConf = conf["entities"]["bird"];

            size_t typeSize = type.size();

            for (size_t textId = 0; textId < typeSize; textId++) {
                if (!type[textId].has_value() || !score[textId].has_value() || !text[textId].has_value()) {
                    continue;
                }
                if (type[textId].value().type != EntityType::TEXT) {
                    continue;
                }
                for (size_t pipeId = 0; pipeId < typeSize; pipeId++) {
                    if (!type[pipeId].has_value() || !score[pipeId].has_value() || !pos[pipeId].has_value()) {
                        continue;
                    }
                    if (type[pipeId].value().type != EntityType::PIPE) {
                        continue;
                    }
                    if (score[pipeId].value().score > 0) {
                        continue;
                    }
                    if (pos[pipeId].value().x > birdConf["position"]["x"]) {
                        continue;
                    }
                    score[pipeId]->score = 1;
                    score[textId]->score += 1;
                    text[textId]->text = std::to_string(score[textId]->score);
                    return;
                }
            }
        } catch (std::exception &e) {
            Logger::error("Failed to load config: " + std::string(e.what()));
        }
    }
} // namespace ECS