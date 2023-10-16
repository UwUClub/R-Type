#include "KeyboardEvent.hpp"

// -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::KeyboardEvent::KeyboardEvent(const KeyIdentifier &aKeyId, const KeyState &aKeyState,
                                         const bool &aIsShiftPressed, const bool &aIsCtrlPressed,
                                         const bool &aIsAltPressed, const bool &aIsSystemPressed)
    : _keyId(aKeyId),
      _state(aKeyState),
      _isShiftPressed(aIsShiftPressed),
      _isCtrlPressed(aIsCtrlPressed),
      _isAltPressed(aIsAltPressed),
      _isSystemPressed(aIsSystemPressed)
{}
