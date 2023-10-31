#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::movePipes()
    {
        auto &world = Core::World::getInstance();
        auto &pos = world.getComponent<Utils::Vector2f>();
        auto &type = world.getComponent<Component::TypeEntity>();
        auto &speed = world.getComponent<Component::Speed>();
        auto &score = world.getComponent<Component::Score>();

        auto &configReader = ConfigReader::getInstance();
        auto &conf = configReader.loadConfig(CONFIG_PATH);
        float pipeLoopWidth = conf["entities"]["pipes"]["loop_width"];

        for (size_t i = 0; i < pos.size(); i++) {
            if (!pos[i].has_value() || !type[i].has_value() || !speed[i].has_value() || !score[i].has_value()) {
                continue;
            }
            auto &typeVal = type[i].value().type;
            if (typeVal != EntityType::PIPE) {
                continue;
            }
            auto &posVal = pos[i].value();
            auto &speedVal = speed[i].value().speed;

            posVal.x -= speedVal * Core::World::getInstance().getDeltaTime();
            if (posVal.x <= -pipeLoopWidth / 2) {
                posVal.x = pipeLoopWidth / 2;
                if (score[i].value().score == 1) {
                    score[i]->score = 0;
                }
            }
        }
    }
} // namespace ECS
