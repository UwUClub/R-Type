#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <any>
#include <cstddef>
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
            using func = std::function<void(EventManager &)>;
            using Callback = std::function<void(std::any)>;
            using CallbackPair = std::pair<std::type_index, Callback>;
            using Callbacks = std::vector<CallbackPair>;

        private:
            EventManager();

            std::unordered_map<std::type_index, std::any> _eventsHandler;
            std::unordered_map<std::type_index, func> _clearFunctions;
            std::unordered_map<std::type_index, Callbacks> _callbacks;

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
             * @brief Subscribe to an event, the callback will be called when the event is published
             *
             * @tparam Event The type of the event to subscribe to
             * @param aCallback The callback to call when the event is published, it takes a pointer to the event as
             * parameter
             */
            template<typename Event>
            void subscribe(std::function<void(Event *)> aCallback)
            {
                auto type = std::type_index(typeid(Event));
                auto typeFunc = std::type_index(typeid(aCallback));

                CallbackPair callbackPair(typeFunc, [=](std::any aEvent) {
                    aCallback(std::any_cast<Event *>(aEvent));
                });

                if (_callbacks.find(type) == _callbacks.end()) {
                    _callbacks[type] = Callbacks();
                }

                _callbacks[type].push_back(callbackPair);
            }

            /**
             * @brief Unsubscribe from an event
             *
             * @tparam Event The type of the event to unsubscribe from
             * @param aCallback The callback to unsubscribe
             */
            template<typename Event>
            void unsubscribe(std::function<void(Event *)> aCallback)
            {
                auto type = std::type_index(typeid(Event));
                auto typeFunc = std::type_index(typeid(aCallback));

                if (_callbacks.find(type) == _callbacks.end()) {
                    return;
                }

                auto callbacks = _callbacks[type];
                for (auto it = std::begin(callbacks); it != std::end(callbacks); ++it) {
                    if (it->first == typeFunc) {
                        _callbacks[type].erase(it);
                        break;
                    }
                }
            }

            /**
             * @brief Publish an event, all the callbacks subscribed to this event will be called
             *
             * @tparam Event The type of the event to publish
             * @param aEvent The event to publish
             */
            template<typename Event>
            void publish(Event *aEvent)
            {
                auto type = std::type_index(typeid(Event));
                auto eventSmartPtr = std::unique_ptr<Event>(aEvent);

                if (_callbacks.find(type) == _callbacks.end()) {
                    return;
                }

                for (auto &callback : _callbacks[type]) {
                    callback.second(eventSmartPtr.get());
                }
            }

            /**
             * @brief Get an Hander linked to an event
             *
             * @tparam Event The type of the event to get the handler
             * @return EventHandler<Event>& The handler of the event.
             */
            template<typename Event>
            EventHandler<Event> &getHandler()
            {
                auto eventTypeIndex = std::type_index(typeid(Event));

                try {
                    if (_eventsHandler.find(eventTypeIndex) == _eventsHandler.cend()) {
                        _eventsHandler[eventTypeIndex] = EventHandler<Event>();
                        _clearFunctions[eventTypeIndex] = [](EventManager &aManager) {
                            auto &myHandler = aManager.getHandler<Event>();

                            myHandler.clearEvents();
                        };
                    }
                    auto &handler = _eventsHandler.at(eventTypeIndex);
                    auto &component = std::any_cast<EventHandler<Event> &>(handler);

                    return component;
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("There is no handler of this type");
                }
            }

            /**
             * @brief Push an event to the queue
             * @details Doesn't call the subscribers
             * @param aEvent The event to push.
             * @tparam Event The type of the event.
             */
            template<typename Event>
            void pushEvent(const Event &aEvent)
            {
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
            template<typename Event>
            std::vector<Event> &getEventsByType()
            {
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
            template<typename Event>
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

            /**
             * @brief Remove an event from the queue
             * @param aIndexes The indexes of the event to remove.
             * @tparam Event The type of the event.
             *
             */
            template<typename Event>
            void removeEvent(std::vector<size_t> aIndexes)
            {
                auto eventIndex = std::type_index(typeid(Event));

                if (_eventsHandler.find(eventIndex) == _eventsHandler.end()) {
                    return;
                }
                try {
                    auto &handler = getHandler<Event>();

                    for (size_t i = 0; i < aIndexes.size(); i++) {
                        size_t idx = aIndexes[i] - i;

                        handler.removeEvent(idx);
                    }
                } catch (const std::bad_any_cast &e) {
                    throw EventManagerException("Can't remove event");
                }
            }

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