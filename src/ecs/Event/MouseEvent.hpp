#ifndef MOUSEEVENT_HPP
#define MOUSEEVENT_HPP

#include "Utils.hpp"

namespace ECS::Event {

    enum class MouseButton
    {
        LEFT = 0,  /*!< The left mouse button. */
        RIGHT = 1, /*!< The right mouse button. */
        MIDDLE = 2 /*!< The middle (wheel) mouse button. */
    };

    enum class MouseState
    {
        RELEASED = 0, /*!< The mouse button is released. */
        PRESSED = 1   /*!< The mouse button is pressed. */
    };

    using MousePosition = ECS::Utils::Vector2i;

    /**
     * @brief Mouse event class is the base class of all mouse events
     */
    class MouseEvent
    {
        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Mouse Event object
             *
             * @param aX The x position of the mouse.
             * @param aY The y position of the mouse.
             * @param aButton The mouse button.
             * @param aState The mouse button state.
             * @param aIsMoving Is the mouse moving.
             * @param aIsAltPressed Is the left alt key pressed.
             * @param aIsShiftPressed Is the left shift key pressed.
             * @param aIsCtrlPressed Is the left ctrl key pressed.
             */
            MouseEvent(const int &aX, const int &aY, const MouseButton &aButton, const MouseState &aState,
                       const bool &aIsMoving = false, const bool &aIsAltPressed = false,
                       const bool &aIsShiftPressed = false, const bool &aIsCtrlPressed = false);

            //-------------------ATTRIBUTES-------------------//
            const MousePosition _position; /*!< The position of the mouse. */
            const MouseButton _button;     /*!< The mouse button. */
            const MouseState _state;       /*!< The mouse button state. */
            bool _isMoving;                /*!< Is the mouse moving. */
            bool _isAltPressed;            /*!< Is the left alt key pressed. */
            bool _isShiftPressed;          /*!< Is the left shift key pressed. */
            bool _isCtrlPressed;           /*!< Is the left ctrl key pressed. */
    };
} // namespace ECS::Event

#endif // !
