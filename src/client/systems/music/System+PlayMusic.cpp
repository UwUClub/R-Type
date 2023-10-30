//
// Created by beafowl on 30/10/23.
//

#include "System.hpp"
#include "EwECS/Music/Music.hpp"

namespace ECS {
    void System::playMusic(ECS::Core::SparseArray<Component::MusicComponents> &aMusic)
    {
        ECS::Music music;

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value()) {
                continue;
            }
            if (music.isPlaying(musicComponent.value()._path) || musicComponent.value()._isPlayed) {
                continue;
            }

            music.play(musicComponent.value()._path, musicComponent.value()._loop, musicComponent.value()._volume);
            musicComponent.value()._isPlayed = true;
        }
    }
}
