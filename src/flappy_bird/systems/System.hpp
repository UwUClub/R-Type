#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <SDL.h>
#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"
#include <unordered_map>

namespace ECS {
    class System
    {
        public:
            /**
             * @brief Apply gravity to entities submitted to it
             *
             * @param aPos SparseArray of all entities position
             * @param aWeight Sparsearray of all entities weight
             */
            static void applyGravity(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::Weight> &aWeight);

            /**
             * @brief Make an entity jump
             *
             * @param aPos SparseArray of all entities position
             * @param aJump Sparsearray of all entities who can jump
             */
            static void jump(Core::SparseArray<ECS::Utils::Vector2f> &aPos, Core::SparseArray<Component::Jump> &aJump);

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
             */
            static void displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
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
