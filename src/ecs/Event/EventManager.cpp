#include "EventManager.hpp"
#include <memory>
#include "Event.hpp"

//-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::EventManager::EventManager() = default;

ECS::Event::EventManager::~EventManager()
{
    _events.clear();
}

//-------------------PUBLIC METHODS-------------------//
void ECS::Event::EventManager::pushEvent(Event *aEvent)
{
    _events.push_back(std::unique_ptr<Event>(aEvent));
}

ECS::Event::EventManager *ECS::Event::EventManager::getInstance()
{
    static EventManager instance;

    return &instance;
}

std::vector<std::unique_ptr<ECS::Event::Event>> &ECS::Event::EventManager::getEvents()
{
    return _events;
}

std::vector<ECS::Event::Event *> ECS::Event::EventManager::getEventsByType(const EventType &aEventType)
{
    std::vector<Event *> events;

    for (auto &event : _events) {
        if (event->getType() == aEventType) {
            events.push_back(event.get());
        }
    }
    return events;
}

void ECS::Event::EventManager::clearNonGameEvents()
{
    for (auto it = _events.begin(); it != _events.end();) {
        if ((*it)->getType() != EventType::GAME) {
            it = _events.erase(it);
        } else {
            ++it;
        }
    }
}

void ECS::Event::EventManager::removeEvent(Event *aEvent)
{
    for (auto it = _events.begin(); it != _events.end();) {
        if (it->get() == aEvent) {
            it = _events.erase(it);
        } else {
            ++it;
        }
    }
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
