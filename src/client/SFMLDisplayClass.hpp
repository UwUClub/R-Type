/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <string>
#include "Components.hpp"
#include "LoadedSprite.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include <unordered_map>

class SFMLDisplayClass
{
    public:
        /**
         * @brief Destroy the SFMLDisplayClass object
         *
         */
        ~SFMLDisplayClass();

        /**
         * @brief Get an Instance of the SFMLDisplayClass (singleton)
         *
         * @return SFMLDisplayClass&
         */
        static SFMLDisplayClass &getInstance()
        {
            static SFMLDisplayClass instance;

            return instance;
        }

        /**
         * @brief Get the texture object
         *
         * @return sf::Texture*
         */
        sf::Texture *getTexture(const std::string &path);

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
        sf::RenderWindow _window;
        std::string _assetPath;

    private:
        std::unordered_map<std::string, sf::Texture *> _textures;
        /**
         * @brief Construct a new SFMLDisplayClass object
         *
         */
        SFMLDisplayClass();
};

#endif /* !SDLDISPLAYClass_HPP_ */
