/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <iostream>
#include <mutex>
#include <vector>

namespace ECS::Event {

    template<class Event>
    class EventHandler
    {
        public:
            using containerT = std::vector<Event>;
            using containerTRef = std::vector<Event> &;
            using containerTConstRef = const std::vector<Event> &;

        private:
            containerT _events;
            std::mutex _mutex;

        public:
            EventHandler() = default;
            ~EventHandler() = default;

            EventHandler(const EventHandler &aOther)
                : _events(aOther._events)
            {}

            EventHandler(EventHandler &&aOther) noexcept
                : _events(std::move(aOther._events))
            {}

            EventHandler &operator=(const EventHandler &aOther)
            {
                _events = aOther._events;
                return *this;
            }

            EventHandler &operator=(EventHandler &&aOther) noexcept
            {
                _events = std::move(aOther._events);
                return *this;
            }

            /**
             * @brief Push an Event
             *
             * @param aEvent the new event to add
             */
            void pushEvent(const Event &aEvent)
            {
                if (!_mutex.try_lock()) {
                    std::cerr << "Waiting for mutex push event" << std::endl;
                }
                std::cout << "Pushing event" << std::endl;
                _events.push_back(aEvent);
                _mutex.unlock();
            }

            /**
             * @brief Get the Events object
             *
             * @return containerTRef the list of events
             */
            containerTRef getEvents()
            {
                return _events;
            }

            /**
             * @brief Get the Events object
             *
             * @return containerTConstRef the list of events
             */
            containerTConstRef getEvents() const
            {
                return _events;
            }

            /**
             * @brief Erase all the events
             *
             */
            void clearEvents()
            {
                while (!_mutex.try_lock()) {
                    std::cerr << "Waiting for mutex clearing events" << std::endl;
                }
                std::cout << "Clearing events" << std::endl;
                _events.clear();
                _mutex.unlock();
            }

            void removeEvent(const std::size_t aIdx)
            {
                if (aIdx >= _events.size()) {
                    return;
                }
                while (!_mutex.try_lock()) {
                    std::cerr << "Waiting for mutex removing event" << std::endl;
                }
                std::cout << "Removing event" << std::endl;
                _events.erase(_events.begin() + aIdx);
                _mutex.unlock();
            }
    };
} // namespace ECS::Event
#endif /* !EVENTHANDLER_HPP_ */
