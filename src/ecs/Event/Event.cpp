#include "Event.hpp"

// -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::Event::Event(const ECS::Event::EventType &aEventType)
    : _type(aEventType)
{}

// -------------------PUBLIC METHODS-------------------//
const ECS::Event::EventType &ECS::Event::Event::getType() const
{
    return _type;
}
