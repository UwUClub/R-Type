/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EventManagerTest
*/

#ifndef _EVENTMANAGERTEST_HPP_
#define _EVENTMANAGERTEST_HPP_

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <vector>

namespace ECS::Event {

    /**
     * @brief A singleton class that manages the events
     *
     */
    class EventManager
    {
        private:
            using Callback = std::function<void(std::any)>;
            using CallbackPair = std::pair<std::type_index, Callback>;
            using Callbacks = std::vector<CallbackPair>;

            std::unordered_map<std::type_index, Callbacks> _callbacks;

            //-------------------CONSTRUCTOR / DESTRUCTOR-------------------//
            EventManager() = default;
            ~EventManager() = default;

        public:
            //-------------------OPERATORS-------------------//
            EventManager(EventManager const &) = delete;
            EventManager &operator=(EventManager const &) = delete;
            EventManager(EventManager &&) = delete;
            EventManager &operator=(EventManager &&) = delete;

            //-------------------METHODS-------------------//
            /**
             * @brief Get the Instance object of the singleton
             *
             * @return EventManager* A pointer to the instance of the singleton
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

                for (auto it = _callbacks[type].begin(); it != _callbacks[type].end(); ++it) {
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

        private:
    };
} // namespace ECS::Event
#endif // !
