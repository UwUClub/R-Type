/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Audio
*/

#pragma once

#include <string>
extern "C"
{
#include "raylib.h"
}

namespace Raylib {
    void initAudioDevice();
    void closeAudioDevice();
    bool isAudioDeviceReady();
    void setMasterVolume(float volume);

    class Sound
    {
        public:
            Sound(const std::string &fileName, float volume = 0.5f);
            bool isReady() const;
            void unload();
            void play() const;
            void stop() const;
            void pause() const;
            void resume() const;
            bool isPlaying() const;
            void setVolume(float volume) const;
            void setPitch(float pitch) const;
            void setPan(float pan) const;
            bool NeedToPlay() const;
            void setNeedToPlay(bool needToPlay);
            std::string getPath() const;
            std::string getRealPath() const;

        private:
            std::string _path;
            std::string _realPath;
            ::Sound _sound;
            bool _needToPlay {false};
    };

    class Music
    {
        public:
            Music(const std::string &fileName, float volume = 0.5f);
            void unload();
            bool isReady() const;
            void play() const;
            bool isPlaying() const;
            void update() const;
            void stop() const;
            void pause() const;
            void resume() const;
            void setVolume(float volume) const;
            void setPitch(float pitch) const;
            void setPan(float pan) const;
            float getTimeLength() const;
            float getTimePlayed() const;
            bool NeedToPlay() const;
            void setNeedToPlay(bool needToPlay);
            std::string getPath() const;
            std::string getRealPath() const;

        private:
            std::string _path;
            std::string _realPath;
            ::Music _music;
            bool _needToPlay {false};
    };
} // namespace Raylib
