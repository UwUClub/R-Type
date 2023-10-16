#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <any>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <typeindex>
#include <vector>
#include "EventHandler.hpp"
#include <unordered_map>
namespace ECS::Event {
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
             * @brief Get the Handler object
             *
             * @tparam Event The type of the event.
             * @return EventHandler<Event>& The handler of the event.
             */
            template<class Event>
            EventHandler<Event> &getHandler()
            {
                try {
                    auto &handler = _eventsHandler.at(std::type_index(typeid(Event)));
                    auto &component = std::any_cast<EventHandler<Event> &>(handler);

                    return component;
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("There is no handler of this type");
                }
            }

            /**
             * @brief Push an event to the queue
             *
             * @param aEvent The event to push.
             * @tparam Event The type of the event.
             */
            template<class Event>
            void pushEvent(const Event &aEvent)
            {
                auto eventIndex = std::type_index(typeid(Event));

                if (_eventsHandler.find(eventIndex) == _eventsHandler.end()) {
                    _eventsHandler[eventIndex] = EventHandler<Event>();
                    _clearFunctions[eventIndex] = [](EventManager &aManager) {
                        auto &myHandler = aManager.getHandler<Event>();

                        myHandler.clearEvents();
                    };
                }
                try {
                    auto &handler = getHandler<Event>();

                    handler.pushEvent(aEvent);
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("Can't push event");
                }
            }

            /**
             * @brief Get all the events of a specific type
             * @tparam Event The type of the event.
             * @return std::vector<Event>& The list of events.
             */
            template<class Event>
            std::vector<Event> &getEventsByType()
            {
                auto eventIndex = std::type_index(typeid(Event));

                if (_eventsHandler.find(eventIndex) == _eventsHandler.end()) {
                    _eventsHandler[eventIndex] = EventHandler<Event>();
                    _clearFunctions[eventIndex] = [](EventManager &aManager) {
                        auto &myHandler = aManager.getHandler<Event>();

                        myHandler.clearEvents();
                    };
                }
                try {
                    auto &handler = getHandler<Event>();

                    return handler.getEvents();
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("Can't get events");
                }
            }

            /**
             * @brief Clear all the events of the types that aren't in the list
             * @tparam EventList The list of events to keep.
             */
            template<typename... EventList>
            void keepEventsAndClear()
            {
                std::vector<std::type_index> eventIndexList = {std::type_index(typeid(EventList))...};

                for (auto &lam : _clearFunctions) {
                    if (std::find(eventIndexList.begin(), eventIndexList.end(), lam.first) == eventIndexList.end()) {
                        lam.second(*this);
                    }
                }
            }

            /**
             * @brief Remove an event from the queue
             * @param aIndex The index of the event to remove.
             * @tparam Event The type of the event.
             *
             */
            template<class Event>
            void removeEvent(const std::size_t aIndex)
            {
                auto eventIndex = std::type_index(typeid(Event));

                if (_eventsHandler.find(eventIndex) == _eventsHandler.end()) {
                    return;
                }
                try {
                    auto &handler = getHandler<Event>();

                    handler.removeEvent(aIndex);
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("Can't remove event");
                }
            }

        private:
            EventManager();
            using func = std::function<void(EventManager &)>;
            std::unordered_map<std::type_index, std::any> _eventsHandler;
            std::unordered_map<std::type_index, func> _clearFunctions;

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

            //-------------------METHODS-------------------//
    };
} // namespace ECS::Event

#endif // !
