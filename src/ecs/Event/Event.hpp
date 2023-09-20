#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

namespace ECS::Event {
    /**
     * @brief Enum of all event types
     *
     */
    enum class EventType
    {
        KEYBOARD,
        MOUSE,
        WINDOW,
        GAME, // These are the events that are not related to the engine but to the game, the game library should create
              // its own events and use this type
        OTHER,
        NONE
    };

    /**
     * @brief Event class is the base class of all events
     *
     */
    class Event
    {
        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Event object
             *
             * @param aEventType The type of the event.
             */
            explicit Event(const EventType &aEventType);

            /**
             * @brief Destroy the Event object
             *
             */
            virtual ~Event() = default;

            //-------------------OPERATORS-------------------//
            /**
             * @brief Construct a new Event object
             *
             * @param aOther The Event to copy.
             */
            Event(const Event &aOther) = default;

            /**
             * @brief Construct a new Event object
             *
             * @param aOther The Event to move.
             */
            Event(Event &&aOther) noexcept = default;

            /**
             * @brief Copy assignment operator
             *
             * @param aOther The Event to copy.
             * @return Event& A reference to the Event.
             */
            Event &operator=(const Event &aOther) = default;

            /**
             * @brief Move assignment operator
             *
             * @param aOther The Event to move.
             * @return Event& A reference to the Event.
             */
            Event &operator=(Event &&aOther) noexcept = default;

            //-------------------METHODS-------------------//
            /**
             * @brief Get the Type object
             *
             * @return const EventType& The type of the event.
             */
            [[nodiscard]] const EventType &getType() const;

        protected:
            EventType _type;
    };
} // namespace ECS::Event

#endif // !