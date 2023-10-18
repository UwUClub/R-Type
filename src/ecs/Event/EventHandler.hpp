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

    /**
     * @brief Class that handle one type of event
     *
     * @tparam Event the type of event to handle
     */
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
            //------------------- CONSTRUCTOR/DESTRUCTOR -------------------//
            /**
             * @brief Construct a new Event Handler object
             *
             */
            EventHandler() = default;
            /**
             * @brief Destroy the Event Handler object
             *
             */
            ~EventHandler() = default;

            //-------------------OPERATORS-------------------//
            EventHandler(const EventHandler &aOther)
                : _events(aOther._events)
            {}

            EventHandler(EventHandler &&aOther) noexcept
                : _events(std::move(aOther._events))
            {}

            EventHandler &operator=(const EventHandler &aOther)
            {
                if (this == &aOther) {
                    return *this;
                }
                _events = aOther._events;
                return *this;
            }

            EventHandler &operator=(EventHandler &&aOther) noexcept
            {
                if (this == &aOther) {
                    return *this;
                }
                _events = std::move(aOther._events);
                return *this;
            }

            //-------------------METHODS-------------------//
            /**
             * @brief Push an Event
             * @details Can wait for the mutex to be unlocked
             * @param aEvent the new event to add to the list
             */
            void pushEvent(const Event &aEvent)
            {
                std::lock_guard<std::mutex> lock(_mutex);

                _events.push_back(aEvent);
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
             * @details Can wait for the mutex to be unlocked
             */
            void clearEvents()
            {
                std::lock_guard<std::mutex> lock(_mutex);

                _events.clear();
            }

            /**
             * @brief Remove an event from the list
             * @details Can wait for the mutex to be unlocked
             * @param aIdx the index of the event to remove
             */
            void removeEvent(const std::size_t aIdx)
            {
                if (aIdx >= _events.size()) {
                    return;
                }
                std::lock_guard<std::mutex> lock(_mutex);

                _events.erase(_events.begin() + aIdx);
            }
    };
} // namespace ECS::Event
#endif /* !EVENTHANDLER_HPP_ */
