#include "EventManager.hpp"

//-------------------PUBLIC METHODS-------------------//
ECS::Event::EventManager *ECS::Event::EventManager::getInstance()
{
    static EventManager instance;

    return &instance;
}
