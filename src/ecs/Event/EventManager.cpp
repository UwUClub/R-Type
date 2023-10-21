#include "EventManager.hpp"
#include <memory>

//-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
ECS::Event::EventManager::EventManager() = default;

ECS::Event::EventManager::~EventManager() = default;

//-------------------PUBLIC METHODS-------------------//

ECS::Event::EventManager *ECS::Event::EventManager::getInstance()
{
    static EventManager instance;

    return &instance;
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