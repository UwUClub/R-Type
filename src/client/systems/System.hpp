#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"

namespace ECS {
    class System
    {
        public:
            /**
             * @brief Move the player
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void movePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Get the all the input of the user
             *
             */

            static void getInput();

            /**
             * @brief Close the SDL window
             *
             */
            static void quitSDL();

            /**
             * @brief Load all the textures of the game
             *
             * @param aSprites SparseArray of all the entities sprites
             */
            static void loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites);

            /**
             * @brief Display all the entities on the screen
             *
             * @param aSprites SparseArray of all the entities sprites
             * @param aPos SparseArray of all the entities position
             */
            static void displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                        Core::SparseArray<Utils::Vector2f> &aPos);

            /**
             * @brief Handle the background's movements
             * @details Background are the entities with the TypeEntity::isBackground set to true
             * @param aPos The position of the background
             * @param aSpeed The speed of the background
             * @param aType The type of the background
             */
            static void moveBackground(Core::SparseArray<Utils::Vector2f> &aPos,
                                       Core::SparseArray<Component::Speed> &aSpeed,
                                       Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Spawn enemies
             *
             */
            static void spawnEnemies();

            /**
             * @brief Move enemies on the screen
             * 
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void moveEnemies(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::Speed> &aSpeed,
                                     Core::SparseArray<Component::TypeEntity> &aType);


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
