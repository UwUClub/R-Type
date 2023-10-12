#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <functional>
#include "ClientGameEvent.hpp"
#include "Components.hpp"
#include "IsAlive.hpp"
#include "KeyboardEvent.hpp"
#include "SparseArray.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"
#include "components/HitBox.hpp"
#include <unordered_map>

namespace ECS {
    class System
    {
        public:
            //----------------------------BACKGROUND----------------------------//
            /**
             * @brief Create local background once connected to server (triggered by server)
             */
            static void createBackground(RType::ClientGameEvent *aEvent);

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

            //----------------------------BONUS----------------------------//
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

            //----------------------------PLAYER----------------------------//
            /**
             * @brief Move the player
             * @brief Move the player (locally, send to server)
             *
             * @param aEvent The keyboard event
             */
            static void movePlayer(Event::KeyboardEvent *aEvent);

            /**
             * @brief Make player shoot missiles when space is pressed (triggered locally, send to server)
             *
             * @param aEvent The keyboard event
             */
            static void triggerPlayerShoot(Event::KeyboardEvent *aEvent);

            //----------------------------BOT----------------------------//
            /**
             * @brief Create a bot (triggered by server)
             */
            static void createBot(RType::ClientGameEvent *aEvent);

            /**
             * @brief Update a bot position (triggered by server)
             *
             */
            static void updateBotPosition(RType::ClientGameEvent *aEvent);

            /**
             * @brief Make bots shoot missiles (triggered by server)
             *
             */
            static void triggerBotShoot(RType::ClientGameEvent *aEvent);

            /**
             * @brief Handle bots who get hit (locally)
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive component
             * @param HitBox SparseArray of all entities hitbox component
             */
            static void botHit(Core::SparseArray<Utils::Vector2f> &aPos,
                               Core::SparseArray<Component::TypeEntity> &aType,
                               Core::SparseArray<Component::HitBox> &HitBox);

            /**
             * @brief Handle the death of a bot (triggered by server)
             *
             * @param aEvent The server event
             */
            static void triggerBotDeath(RType::ClientGameEvent *aEvent);

            /**
             * @brief Handle the death of a bot (triggered by server)
             * @param aSpeed
             */
            static void triggerBotBonus(RType::ClientGameEvent *aEvent);

            /**
             * @brief Handle the disconnection of a player (triggered by server)
             * @param aEvent The server event containing the player id
             */
            static void triggerBotDisconnect(RType::ClientGameEvent *aEvent);

            //----------------------------INPUT----------------------------//
            /**
             * @brief Get the all the input of the user (locally)
             *
             */
            static void getInput();

            //----------------------------WINDOW----------------------------//
            /**
             * @brief Close the SDL window (locally)
             *
             * @param aEvent The window event
             */
            static void quitSDL(Event::WindowEvent *aEvent);

            //----------------------------DISPLAY----------------------------//
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

            //----------------------------ENEMY----------------------------//
            /**
             * @brief Create an enemy (triggered by server)
             *
             */
            static void createEnemy(RType::ClientGameEvent *aEvent);

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
             * @param
             */
            static void triggerEnemyDeath(RType::ClientGameEvent *aEvent);

            /**
             * @brief Make enemies shoot missiles (triggered by server)
             *
             * @param aEvent The server event containing the enemy id
             */
            static void triggerEnemyShoot(RType::ClientGameEvent *aEvent);

            //----------------------------MISSILES----------------------------//
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

            //----------------------------ERROR MESSAGE----------------------------//
            /**
             * @brief Display error message in case server is full (triggered by server)
             */
            static void createServerFullErrorMessage(RType::ClientGameEvent *aEvent);

        private:
            /**
             * @brief Map of all the SDL_Keycode and their equivalent in our ECS
             *
             */
            static const inline std::unordered_map<SDL_Keycode, const ECS::Event::KeyIdentifier> _keyMap = {
                {SDLK_ESCAPE, ECS::Event::KeyIdentifier::ESCAPE}, {SDLK_UP, ECS::Event::KeyIdentifier::UP},
                {SDLK_DOWN, ECS::Event::KeyIdentifier::DOWN},     {SDLK_LEFT, ECS::Event::KeyIdentifier::LEFT},
                {SDLK_RIGHT, ECS::Event::KeyIdentifier::RIGHT},   {SDLK_SPACE, ECS::Event::KeyIdentifier::SPACE},
            };

            /**
             * @brief Map of all the SDL_WindowEvent and their equivalent in our ECS
             *
             */
            static const inline std::unordered_map<Uint32, const ECS::Event::WindowEventType> _windowEventMap = {
                {SDL_WINDOWEVENT_CLOSE, ECS::Event::WindowEventType::CLOSED},
                {SDL_WINDOWEVENT_RESIZED, ECS::Event::WindowEventType::RESIZED},
                {SDL_WINDOWEVENT_FOCUS_GAINED, ECS::Event::WindowEventType::FOCUSED},
                {SDL_WINDOWEVENT_FOCUS_LOST, ECS::Event::WindowEventType::UNFOCUSED},
            };
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
