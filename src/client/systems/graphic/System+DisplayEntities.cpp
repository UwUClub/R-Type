#include "KeyboardEvent.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "raylib.h"

namespace ECS {
    void System::displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        const auto size = aSprites.size();

        for (auto itx = 0; itx < size; ++itx) {
            if (!aSprites[itx].has_value() || aSprites[itx].value().texture == nullptr) {
                continue;
            }
            const auto &sprite = aSprites[itx].value();
            const auto &pos = aPos[itx].value();
            const auto &rect = sprite.rect;
            const auto &texture = sprite.texture;

            DrawTextureRec(*texture, rect, {pos.x, pos.y}, WHITE);
        }
    }
} // namespace ECS
