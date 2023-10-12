/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include <cstddef>
#include <string>
#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "raylib.h"
#include <unordered_map>

class RayDisplayClass
{
    public:
        /**
         * @brief Destroy the SDLDisplayClass object
         *
         */
        ~RayDisplayClass();

        /**
         * @brief Get an Instance of the SDLDisplayClass (singleton)
         *
         * @return SDLDisplayClass&
         */
        static RayDisplayClass &getInstance()
        {
            static RayDisplayClass instance;

            return instance;
        }

        /**
         * @brief Get the texture object
         *
         * @return SDL_Texture*
         */
        Texture2D *getTexture(const std::string &path);

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

        std::string _assetPath;

    private:
        std::unordered_map<std::string, Texture2D> _textures;
        /**
         * @brief Construct a new SDLDisplayClass object
         *
         */
        RayDisplayClass();
};

#endif /* !SDLDISPLAYClass_HPP_ */
