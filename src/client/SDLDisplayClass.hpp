/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include "Utils.hpp"
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

#include <SDL2/SDL.h>
#include <string>
#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include <SDL_image.h>
#include <unordered_map>

static const std::string BACKGROUND_ASSET = "assets/sprites/background.png";
static const std::string PLAYER_ASSET = "assets/sprites/r-typesheet42.png";
static const std::string ENEMY_ASSET = "assets/sprites/r-typesheet5.png";

class SDLDisplayClass
{
    public:
        /**
         * @brief Destroy the SDLDisplayClass object
         *
         */
        ~SDLDisplayClass();

        /**
         * @brief Get an Instance of the SDLDisplayClass (singleton)
         *
         * @return SDLDisplayClass&
         */
        static SDLDisplayClass &getInstance()
        {
            static SDLDisplayClass instance;

            return instance;
        }

        static size_t addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                Component::LoadedSprite aSprite);
        /**
         * @brief Construct a new SDLDisplayClass object
         *
         */
        SDLDisplayClass();
        SDL_Renderer *_renderer;
        SDL_Window *_window;
        float _elapsedTime;

    private:
};

#endif /* !SDLDISPLAYClass_HPP_ */
