#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <SDL.h>
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
             * @param aWorld A reference to the world
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void movePlayer(Core::World &aWorld, Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<ECS::Utils::Speed> &aSpeed,
                                   Core::SparseArray<ECS::Utils::TypeEntity> &aType);

            /**
             * @brief Get the all the input of the user
             *
             * @param aWorld A reference to the world
             */

            static void getInput(Core::World &aWorld);

            /**
             * @brief Close the SDL window
             *
             * @param aWorld A reference to the world
             */
            static void quitSDL(Core::World &aWorld);

            /**
             * @brief Load all the textures of the game
             *
             * @param aWorld A reference to the world
             * @param aSprites SparseArray of all the entities sprites
             */
            static void loadTextures(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites);

            /**
             * @brief Display all the entities on the screen
             *
             * @param aWorld A reference to the world
             * @param aSprites SparseArray of all the entities sprites
             */
            static void displayEntities(Core::World &aWorld, Core::SparseArray<Utils::LoadedSprite> &aSprites,
                                        Core::SparseArray<Utils::Vector2f> &aPos);

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
