#include "Graphics.hpp"
#include "KeyboardEvent.hpp"
#include "RayDisplayClass.hpp"
#include "Raylib.hpp"
#include "System.hpp"

namespace ECS {
    void System::displayEntities(Core::SparseArray<Raylib::Sprite> &aSprites, Core::SparseArray<Utils::Vector2f> &aPos)
    {
        const auto size = aSprites.size();

        for (auto itx = 0; itx < size; ++itx) {
            if (!aSprites[itx].has_value() || aSprites[itx].value()._texture == nullptr) {
                continue;
            }
            auto &sprite = aSprites[itx].value();
            const auto &pos = aPos[itx].value();

            sprite.draw({pos.x, pos.y}, {255, 255, 255, 255});
        }
    }
} // namespace ECS
