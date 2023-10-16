#ifndef WINDOWEVENT_HPP
#define WINDOWEVENT_HPP

#include "Utils.hpp"

namespace ECS::Event {
    enum class WindowFocusState
    {
        FOCUSED = 0,  /*!< The window is focused. */
        UNFOCUSED = 1 /*!< The window is unfocused. */
    };

    enum class WindowDisplayState
    {
        FULLSCREEN = 0, /*!< The window is fullscreen. */
        WINDOWED = 1,   /*!< The window is windowed. */
        MINIMIZED = 2   /*!< The window is minimized. */
    };

    enum class WindowEventType
    {
        RESIZING = 0, /*!< The window is resizing. */
        RESIZED = 1,  /*!< The window is resized. */
        CLOSED = 2,   /*!< The window is closed. */
        FOCUSED = 3,  /*!< The window is focused. */
        UNFOCUSED = 4 /*!< The window is unfocused. */
    };

    using WindowSize = ECS::Utils::Vector2i;
    using WindowPosition = ECS::Utils::Vector2i;

    /**
     * @brief Window event class is the base class of all window events
     *
     */
    class WindowEvent
    {
        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Window Event object
             *
             * @param aWidth The width of the window.
             * @param aHeight The height of the window.
             * @param aWindowState The state of the window.
             * @param aWindowFocusState The focus state of the window.
             * @param aWindowEventType The type of the window event.
             */
            WindowEvent(const int &aWidth, const int &aHeight, const int &aX, const int &aY,
                        const WindowDisplayState &aWindowState, const WindowFocusState &aWindowFocusState,
                        const WindowEventType &aWindowEventType);

            //-------------------ATTRIBUTES-------------------//
            const WindowSize _size;                   /*!< The size of the window. */
            const WindowPosition _position;           /*!< The position of the window. */
            const WindowDisplayState _windowState;    /*!< Is the window fullscreen. */
            const WindowFocusState _windowFocusState; /*!< Is the window focused. */
            const WindowEventType _windowEventType;   /*!< The type of the window event. */
    };
} // namespace ECS::Event
#endif // !
