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

        /**
         * @brief Get the texture object
         *
         * @return SDL_Texture*
         */
        SDL_Texture *getTexture(const std::string &path);

        static void addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                              Component::LoadedSprite aSprite, Component::HitBox aHitBox, Component::IsAlive aIsAlive);
        SDL_Renderer *_renderer;
        SDL_Window *_window;
        float _elapsedTime;

    private:
        std::unordered_map<std::string, SDL_Texture *> _textures;
        /**
         * @brief Construct a new SDLDisplayClass object
         *
         */
        SDLDisplayClass();
};

#endif /* !SDLDISPLAYClass_HPP_ */
