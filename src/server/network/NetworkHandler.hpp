#include <boost/asio.hpp>
#include <map>

#ifndef NETWORKHANDLER_HPP
#define NETWORKHANDLER_HPP

using boost::asio::ip::udp;

enum class NetworkEvent {
    CONNECT = 0,
    DISCONNECT,
    CRASH,
    MOVE,
    SHOOT,
    MONSTER_SPAWN,
    MONSTER_DEATH,
    MONSTER_MOVE,
    MONSTER_SHOOT
};

class NetworkHandler {

    private:
    boost::asio::ip::port_type _port;
    boost::asio::io_context _ioContext;
    udp::socket _socket;
    //std::map<udp::endpoint, Player> _clients;

    public:
    /**
    * @brief Launch the server
    * @param port The port to listen to
    */
    explicit NetworkHandler(const unsigned short);
    ~NetworkHandler() = default;

    /**
    * @brief Listen to clients
-    */
    void listen();

    /**
    * @brief Send a message to the server
    * @param buffer The message to send
    * @param clientId The id of the client to send the message to
    */
    void send(const boost::asio::const_buffer, size_t);

    private:
    /**
    * @brief Trigger an event
    * @param error The error code
    * @param bytes_transferred The number of bytes transferred
    */
    void triggerEvent(const boost::system::error_code &, std::size_t);
};

#endif
