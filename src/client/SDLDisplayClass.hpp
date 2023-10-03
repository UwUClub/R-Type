/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include <SDL2/SDL.h>
#include <string>
#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include <SDL_image.h>
#include <unordered_map>

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

        static void addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
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
