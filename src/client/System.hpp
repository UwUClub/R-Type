#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <SDL2/SDL.h>
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
             * @param world a reference to the world
             * @param pos SparseArray of all entities position
             * @param speed Sparsearray of all entities speed
             * @param type SparseArray of all entities type
             */
            static void movePlayer(Core::World &world, Core::SparseArray<ECS::Utils::Vector2f> &pos,
                                   Core::SparseArray<ECS::Utils::Speed> &speed,
                                   Core::SparseArray<ECS::Utils::TypeEntity> &type);
        
            /**
             * @brief Get the all the input of the user
             * 
             * @param world A reference to the world
             */

            static void getInput(Core::World &world);

            /**
             * @brief Close the SDL window
             * 
             * @param world A reference to the world
             */
            static void quitSDL(Core::World &world);

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
