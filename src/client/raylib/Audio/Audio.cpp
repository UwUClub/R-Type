/*
** EPITECH PROJECT, 2023
** R-Bus
** File description:
** Audio
*/

#include "Audio.hpp"
#include "ResourcesManager.hpp"

namespace Raylib {

    // Audio device management functions

    void initAudioDevice()
    {
        InitAudioDevice();
    }

    void closeAudioDevice()
    {
        CloseAudioDevice();
    }

    bool isAudioDeviceReady()
    {
        return IsAudioDeviceReady();
    }

    void setMasterVolume(float volume)
    {
        SetMasterVolume(volume);
    }

    // Sounds
    Sound::Sound(const std::string& fileName, float volume)
        : _path(fileName),
          _realPath(ECS::ResourcesManager::convertPath(fileName)),
          _sound(LoadSound(_realPath.c_str()))
    {
        SetSoundVolume(_sound, volume);
    }

    bool Sound::isReady() const
    {
        return IsSoundReady(_sound);
    }

    void Sound::unload()
    {
        UnloadSound(_sound);
    }

    void Sound::play() const
    {
        PlaySound(_sound);
    }

    void Sound::stop() const
    {
        StopSound(_sound);
    }

    void Sound::pause() const
    {
        PauseSound(_sound);
    }

    void Sound::resume() const
    {
        ResumeSound(_sound);
    }

    bool Sound::isPlaying() const
    {
        return IsSoundPlaying(_sound);
    }

    void Sound::setVolume(float volume) const
    {
        SetSoundVolume(_sound, volume);
    }

    void Sound::setPitch(float pitch) const
    {
        SetSoundPitch(_sound, pitch);
    }

    void Sound::setPan(float pan) const
    {
        SetSoundPitch(_sound, pan);
    }

    bool Sound::NeedToPlay() const
    {
        return _needToPlay;
    }

    void Sound::setNeedToPlay(bool needToPlay)
    {
        _needToPlay = needToPlay;
    }

    std::string Sound::getPath() const
    {
        return _path;
    }

    std::string Sound::getRealPath() const
    {
        return _realPath;
    }

    // Music

    Music::Music(const std::string& fileName, float volume)
        : _path(fileName),
          _realPath(ECS::ResourcesManager::convertPath(fileName)),
          _music(LoadMusicStream(_realPath.c_str()))
    {
        SetMusicVolume(_music, volume);
    }

    void Music::unload()
    {
        UnloadMusicStream(_music);
    }

    bool Music::isReady() const
    {
        return IsMusicReady(_music);
    }

    void Music::play() const
    {
        PlayMusicStream(_music);
    }

    bool Music::isPlaying() const
    {
        return IsMusicStreamPlaying(_music);
    }

    void Music::update() const
    {
        UpdateMusicStream(_music);
    }

    void Music::stop() const
    {
        StopMusicStream(_music);
    }

    void Music::pause() const
    {
        PauseMusicStream(_music);
    }

    void Music::resume() const
    {
        ResumeMusicStream(_music);
    }

    void Music::setVolume(float volume) const
    {
        SetMusicVolume(_music, volume);
    }

    void Music::setPitch(float pitch) const
    {
        SetMusicPitch(_music, pitch);
    }

    void Music::setPan(float pan) const
    {
        SetMusicPitch(_music, pan);
    }

    float Music::getTimeLength() const
    {
        return GetMusicTimeLength(_music);
    }

    float Music::getTimePlayed() const
    {
        return GetMusicTimePlayed(_music);
    }

    bool Music::NeedToPlay() const
    {
        return _needToPlay;
    }

    void Music::setNeedToPlay(bool needToPlay)
    {
        _needToPlay = needToPlay;
    }

    std::string Music::getPath() const
    {
        return _path;
    }

    std::string Music::getRealPath() const
    {
        return _realPath;
    }
} // namespace Raylib
