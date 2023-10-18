#include "MouseEvent.hpp"

// -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::MouseEvent::MouseEvent(const int &aX, const int &aY, const MouseButton &aButton, const MouseState &aState,
                                   const bool &aIsMoving, const bool &aIsAltPressed, const bool &aIsShiftPressed,
                                   const bool &aIsCtrlPressed)
    : _position(aX, aY),
      _button(aButton),
      _state(aState),
      _isMoving(aIsMoving),
      _isAltPressed(aIsAltPressed),
      _isShiftPressed(aIsShiftPressed),
      _isCtrlPressed(aIsCtrlPressed)
{}