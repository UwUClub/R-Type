#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <typeindex>
#include <vector>
#include "Event.hpp"
#include <unordered_map>

namespace ECS::Event {
    class Event;

    /**
     * @brief EventManager class is a singleton that manage all events
     *
     */
    class EventManager final
    {
        public:
            //------------------- DESTRUCTOR-------------------//
            /**
             * @brief Destroy the Event Manager object
             *
             */
            ~EventManager();

            //-------------------OPERATORS-------------------//
            /**
             * @brief Copy assignment operator, delete because singleton.
             *
             * @param aOther The EventManager to copy.
             */
            EventManager(const EventManager &aOther) = delete;

            /**
             * @brief Move assignment operator, delete because singleton.
             *
             * @param aOther The EventManager to move.
             */
            EventManager(EventManager &&aOther) noexcept = delete;

            /**
             * @brief Copy assignment operator, delete because singleton.
             *
             * @param aOther The EventManager to copy.
             * @return EventManager& A reference to the EventManager.
             */
            EventManager &operator=(const EventManager &aOther) = delete;

            /**
             * @brief Move assignment operator, delete because singleton.
             *
             * @param aOther The EventManager to move.
             * @return EventManager& A reference to the EventManager.
             */
            EventManager &operator=(EventManager &&aOther) noexcept = delete;

            //-------------------METHODS-------------------//
            /**
             * @brief Get the Instance object (singleton)
             *
             * @return EventManager* A pointer to the EventManager.
             */
            static EventManager *getInstance();

            /**
             * @brief Push an event to the queue
             *
             * @param aEvent The event to push.
             */
            void pushEvent(Event *aEvent);

            /**
             * @brief Get the Events object
             *
             * @return std::vector<Event>& A reference to the vector of events.
             */
            [[nodiscard]] std::vector<Event *> &getEvents();

            /**
             * @brief Get all the events of a specific type
             *
             */
            std::vector<Event *> getEventsByType(const EventType &aEventType);

            /**
             * @brief Clear all the events
             *
             */
            void clearEvents();

        private:
            EventManager();
            std::vector<Event *> _events;

        private:
            //-------------------EXCEPTIONS-------------------//
            class EventManagerException : public std::exception
            {
                public:
                    explicit EventManagerException(const std::string &aMessage);
                    ~EventManagerException() override = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string _message;
            };
    };
} // namespace ECS::Event

#endif // !
