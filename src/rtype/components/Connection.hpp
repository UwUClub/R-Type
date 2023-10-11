#include <string>
#include "NetworkHandler.hpp"

#ifndef CONNECTION_STATUS_HPP
    #define CONNECTION_STATUS_HPP

namespace Component {
    struct Connection
    {
            /**
             * @brief Construct a new ConnectionStatus object
             *
             */
            Connection()
                : status(Network::ConnectionStatus::PENDING)
            {}
            /**
             * @brief Construct a new ConnectionStatus object
             *
             * @param aStatus The status of the entity
             */
            explicit Connection(Network::ConnectionStatus aStatus)
                : status(aStatus)
            {}

            Network::ConnectionStatus status;
            float age;
    };
} // namespace Component
#endif // DEBUG