//
// Created by beafowl on 30/10/23.
//

#include "AssetManager.hpp"
#include "EwECS/Music/Music.hpp"
#include "EwECS/Music/MusicComponent.hpp"
#include "System.hpp"

namespace ECS {
    void System::createMusic(ECS::Core::SparseArray<Component::MusicComponents> &aMusic)
    {
        ECS::Music music;

        aMusic[0] = Component::MusicComponents("assets/sounds/r-type.ogg", true, 20, false);

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value()) {
                continue;
            }
            music.createMusic("assets/sounds/r-type.ogg");
        }
    }
} // namespace ECS
