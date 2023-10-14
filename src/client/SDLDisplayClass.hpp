/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include <SDL2/SDL.h>
#include <cstddef>
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

        /**
         * @brief Free the rects of the entity
         *
         * @param idx The index of the entity
         */
        void freeRects(const std::size_t &idx);

        /**
         * @brief Create a new entity object
         *
         * @param aPos Position of the entity
         * @param aSpeed Speed of the entity
         * @param aType Type of the entity
         * @param aSprite Sprite of the entity
         * @param aHitBox Hitbox of the entity
         * @param aIsAlive IsAlive of the entity
         * @return size_t The index of the entity
         */
        static size_t addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                Component::LoadedSprite aSprite, Component::HitBox aHitBox,
                                Component::IsAlive aIsAlive);
        SDL_Renderer *_renderer;
        SDL_Window *_window;

    private:
        std::unordered_map<std::string, SDL_Texture *> _textures;
        /**
         * @brief Construct a new SDLDisplayClass object
         *
         */
        SDLDisplayClass();
};

#endif /* !SDLDISPLAYClass_HPP_ */
