#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include "Components.hpp"
#include "IsAlive.hpp"
#include "KeyboardEvent.hpp"
#include "LoadedSprite.hpp"
#include "SparseArray.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"
#include "components/HitBox.hpp"

namespace ECS {
    class System
    {
        public:
            /**
             * @brief Create local background once connected to server (triggered by server)
             */
            static void createBackground();

            /**
             * @brief Handle the move of the bonus
             * @details The bonus is a sprite that is displayed on the screen for a short amount of time on kill of an
             * enemy
             * @param aPos The position of the bonus
             * @param aSpeed The speed of the bonus
             * @param aType The type of the bonus
             */
            static void moveBonus(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                  Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Handle the trigger of the bonus
             * @param aPos The position of the bonus
             * @param aType The type of the bonus
             * @param aIsAlive The isAlive of the bonus
             * @param aHitBox The hitbox of the bonus
             */
            static void triggerBonus(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::TypeEntity> &aType,
                                     Core::SparseArray<Component::IsAlive> &aIsAlive,
                                     Core::SparseArray<Component::HitBox> &aHitBox);

            /**
             * @brief Move the player
             * @brief Move the player (locally, send to server)
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void movePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Create a bot (triggered by server)
             */
            static void createBot();

            /**
             * @brief Update a bot position (triggered by server)
             *
             */
            static void updateBotPosition(Core::SparseArray<Utils::Vector2f> &aPos,
                                          Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Get the all the input of the user (locally)
             *
             */
            static void getInput();

            /**
             * @brief Load all the textures of the game (locally)
             *
             * @param aSprites SparseArray of all the entities sprites
             */
            static void loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites);

            /**
             * @brief Display all the entities on the screen (locally)
             *
             * @param aSprites SparseArray of all the entities sprites
             * @param aPos SparseArray of all the entities position
             */
            static void displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                        Core::SparseArray<Utils::Vector2f> &aPos);

            /**
             * @brief Handle the background's movements (locally)
             * @details Background are the entities with the TypeEntity::isBackground set to true
             *
             * @param aPos The position of the background
             * @param aSpeed The speed of the background
             * @param aType The type of the background
             */
            static void moveBackground(Core::SparseArray<Utils::Vector2f> &aPos,
                                       Core::SparseArray<Component::Speed> &aSpeed,
                                       Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Create an enemy (triggered by server)
             *
             */
            static void createEnemy();

            /**
             * @brief Move enemy on the screen (locally)
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void moveEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                  Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Make player shoot missiles when space is pressed (triggered locally, send to server)
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive component
             */
            static void triggerPlayerShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                           Core::SparseArray<Component::TypeEntity> &aType,
                                           Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Make bots shoot missiles (triggered by server)
             *
             */
            static void triggerBotShoot();

            /**
             * @brief Move missiles on the screen (locally)
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void moveMissiles(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::Speed> &aSpeed,
                                     Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Handle enemies who get hit (locally)
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             */
            static void enemyHit(Core::SparseArray<Utils::Vector2f> &aPos,
                                 Core::SparseArray<Component::TypeEntity> &aType,
                                 Core::SparseArray<Component::HitBox> &aHitBox);

            /**
             * @brief Handle the death of an enemy (triggered by server)
             *
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive component
             * @param aSprites SparseArray of all entities sprites
             */
            static void triggerEnemyDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                          Core::SparseArray<Component::IsAlive> &aIsAlive,
                                          Core::SparseArray<Component::LoadedSprite> &aSprites,
                                          Core::SparseArray<Utils::Vector2f> &aPos);

            /**
             * @brief Make enemies shoot missiles (triggered by server)
             *
             */
            static void triggerEnemyShoot();

            /**
             * @brief Handle bots who get hit (locally)
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param HitBox SparseArray of all entities hitbox component
             */
            static void botHit(Core::SparseArray<Utils::Vector2f> &aPos,
                               Core::SparseArray<Component::TypeEntity> &aType,
                               Core::SparseArray<Component::HitBox> &HitBox);

            /**
             * @brief Handle the death of a bot (triggered by server)
             *
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive component
             * @param aSprites SparseArray of all entities sprites
             */
            static void triggerBotDeath(Core::SparseArray<Component::TypeEntity> &aType,
                                        Core::SparseArray<Component::IsAlive> &aIsAlive,
                                        Core::SparseArray<Component::LoadedSprite> &aSprites);

            /**
             * @brief Handle the death of a bot (triggered by server)
             * @param aSpeed
             */
            static void triggerBotBonus(Core::SparseArray<Component::Speed> &aSpeed,
                                        Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Handle the disconnection of a player (triggered by server)
             */
            static void triggerBotDisconnect(Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Display error message in case server is full (triggered by server)
             */
            static void createServerFullErrorMessage();

        private:
            /**
             * @brief Map of all the SDL_Keycode and their equivalent in our ECS
             *
             */
            static const inline std::unordered_map<sf::Keyboard::Key, const ECS::Event::KeyIdentifier> _keyMap = {
                {sf::Keyboard::Key::Escape, ECS::Event::KeyIdentifier::ESCAPE},
                {sf::Keyboard::Key::Up, ECS::Event::KeyIdentifier::UP},
                {sf::Keyboard::Key::Down, ECS::Event::KeyIdentifier::DOWN},
                {sf::Keyboard::Key::Left, ECS::Event::KeyIdentifier::LEFT},
                {sf::Keyboard::Key::Right, ECS::Event::KeyIdentifier::RIGHT},
                {sf::Keyboard::Key::Space, ECS::Event::KeyIdentifier::SPACE},
            };
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
