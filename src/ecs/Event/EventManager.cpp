#include "EventManager.hpp"
#include <memory>
#include <pthread.h>
#include "Event.hpp"

//-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::EventManager::EventManager() = default;

ECS::Event::EventManager::~EventManager() = default;

//-------------------PUBLIC METHODS-------------------//
void ECS::Event::EventManager::pushEvent(Event &aEvent)
{
    _events.push_back(std::move(aEvent));
}

ECS::Event::EventManager *ECS::Event::EventManager::getInstance()
{
    static EventManager instance;

    return &instance;
}

std::vector<ECS::Event::Event> &ECS::Event::EventManager::getEvents()
{
    return _events;
}

std::vector<ECS::Event::Event> ECS::Event::EventManager::getEventsByType(const EventType &aEventType)
{
    std::vector<Event> events;

    for (auto &event : _events) {
        if (event.getType() == aEventType) {
            events.push_back(event);
        }
    }
    return events;
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
