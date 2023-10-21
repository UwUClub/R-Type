#include "WindowEvent.hpp"

// -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::WindowEvent::WindowEvent(const int &aWidth, const int &aHeight, const int &aX, const int &aY,
                                     const WindowDisplayState &aWindowState, const WindowFocusState &aWindowFocusState,
                                     const WindowEventType &aWindowEventType)
    : _size(aWidth, aHeight),
      _position(aX, aY),
      _windowState(aWindowState),
      _windowFocusState(aWindowFocusState),
      _windowEventType(aWindowEventType)
{}
