#include "EventManager.hpp"
#include <memory>
#include "Event.hpp"

//-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::EventManager::EventManager() = default;

ECS::Event::EventManager::~EventManager()
{
    clearNonGameEvents();
}

//-------------------PUBLIC METHODS-------------------//
void ECS::Event::EventManager::pushEvent(Event *aEvent)
{
    _events.push_back(aEvent);
}

ECS::Event::EventManager *ECS::Event::EventManager::getInstance()
{
    static EventManager instance;

    return &instance;
}

std::vector<ECS::Event::Event *> &ECS::Event::EventManager::getEvents()
{
    return _events;
}

std::vector<ECS::Event::Event *> ECS::Event::EventManager::getEventsByType(const EventType &aEventType)
{
    std::vector<Event *> events;

    for (auto &event : _events) {
        if (event->getType() == aEventType) {
            events.push_back(event);
        }
    }
    return events;
}

void ECS::Event::EventManager::clearNonGameEvents()
{
    for (int i = 0; i < _events.size(); i++) {
        if (_events[i]->getType() != EventType::GAME) {
            delete _events[i];
            _events.erase(_events.begin() + i);
            i--;
        }
    }
}

void ECS::Event::EventManager::removeEvent(int aIndex)
{
    if (aIndex >= _events.size()) {
        throw EventManagerException("Index out of range");
    }
    delete _events[aIndex];
    _events.erase(_events.begin() + aIndex);
}

//-------------------NESTED CLASSES-------------------//
//-------------------EventManagerException-------------------//
ECS::Event::EventManager::EventManagerException::EventManagerException(const std::string &aMessage)
    : _message(aMessage)
{}

const char *ECS::Event::EventManager::EventManagerException::what() const noexcept
{
    return _message.c_str();
}
