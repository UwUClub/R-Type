# Game Protocol for Multiplayer R-Type Game

R-Type is an iconic series of horizontal-scrolling shoot 'em up video games developed by Irem, which began in 1987 in arcades. It is likely inspired by Konami's Gradius series, the first installment of which was released two years earlier.

**A game developed by:**
- Valentin GEGOUX
- Mathéo MARTIN
- Baptiste LARAN
- Maxence LABOUREL

*Epitech Toulouse, promo 2026*
*September 2023*

## Copyright Notice

Copyright (c) The persons identified as the game developers.  All rights reserved.

## Table of Contents

1. [Introduction](#introduction)
2. [Protocol Specification](#protocol-specification)
   2.1. [Packet Types](#packet-types)
   2.2. [Packet Format](#message-format)
   2.3. [Serialization](#security-considerations)
   2.4. [R-Type Protocol Library](#r-type-protocol-library)
3. [Security Considerations](#security-considerations)
4. [Examples](#examples)
7. [Author's Addresses](#authors-addresses)

## 1. Introduction

The multiplayer R-Type game protocol is designed to enable communication
between clients and servers in a multiplayer R-Type game. This protocol
defines various message types and associated data structures for in-game
events, including player interactions and monster behavior.

## 2. Protocol Specification

### 2.1. Packet Types

The protocol defines the following packet types:

**Client to Server Packets:**
- `CONNECT` (0)
- `DISCONNECT` (1)
- `CRASH` (2)
- `MOVE_LEFT` (3)
- `MOVE_UP` (4)
- `MOVE_RIGHT` (5)
- `MOVE_DOWN` (6)
- `SHOOT` (7)

Each client is a game player. The above packets correspond to player actions.

**Server to Client Packets:**
- `PLAYER_CONNECTION` (0)
- `PLAYER_DISCONNECTION` (1)
- `PLAYER_POSITION` (2)
- `PLAYER_SHOOT` (3)
- `PLAYER_DEATH`(4)
- `MONSTER_SPAWN` (5)
- `MONSTER_DEATH` (6)
- `MONSTER_POSITION` (7)
- `MONSTER_SHOOT` (8)

### 2.2. Packet Format

- Each packet has a 4 bytes (*int*) `type` property. It contains the packet type.
- Each "Server to Client" packet has an 8 bytes (*size_t*) `id` property to identify the player or monster concerned by the packet in 8 bytes. It should naturally be common to clients and server.
- The `PLAYER_CONNECTION` packet has a 2 bytes (boolean) `isYou` property. If it's `true`, the receiving client can assign its id as the associated id property.
- The following "Server to Client" packets have a 8 bytes (array of 2 float) `position` property:
    - `PLAYER_POSITION` (2)
    - `MONSTER_SPAWN` (6)
    - `MONSTER_POSITION` (8)

### 2.3. Serialization

The protocol is binary, so packets must be serialized to binary format before being sent. It must naturally be unserialized from binary format before being read.

### 2.4 R-Type Protocol Library

We made a C++ library commonly usable by client and server programs. It requires [Boost Asio](https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html). It defines:
- `ServerToClientPacket` and `ClientToServerPacket` structs,
- `ClientGameEvent` and `ServerGameEvent` classes compatible with our [ECS]() (todo: add ECS download link)
- `serializePacket` and `unserializePacket` functions (see examples).
All under a namespace called `RTypeProtocol`.

(todo: add download)

## 3. Security Considerations

Implementations of this protocol should consider security aspects to protect against unauthorized access, cheating, and other potential vulnerabilities.

Remember that the server should always have the last word on the client.

## 4. Examples

Here is an example of a C++ client sending a `MOVE_UP` packet to a C++ server, both using our RType protocol library and [Boost Asio](https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html):

**Client side**:
```
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include <boost/asio.hpp>
...
// setup socket and serverEndpoint
...
RTypeProtocol::ClientToServerPacket packet;
packet.type = RTypeProtocol::ServerEventType::MOVE_UP;
boost::asio::streambuf buf;

RTypeProtocol::serializePacket<const RTypeProtocol::ClientToServerPacket &>(&buf, packet);
socket.send_to(buf.data(), serverEndpoint);
...
```

**Server side**:
```
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include <boost/asio.hpp>
...
constexpr unsigned short READ_BUFFER_SIZE = 128;
...
std::array<char, READ_BUFFER_SIZE> readBuffer;
...
// fill readBuffer using Boost Asio
...
RTypeProtocol::ClientToServerPacket packet;

RTypeProtocol::unserializePacket<RTypeProtocol::ClientToServerPacket, std::array<char, READ_BUFFER_SIZE>>(&packet, readBuffer);

// you can access packet here (packet.type == MOVE_UP)
...
```

The idea is the same for sending packets in the other direction with `RTypeProtocol::ServerToClientPacket`.

## 5. Author's Addresses

Our email addresses:
- valentin.gegoux@epitech.eu
- matheo.martin@epitech.eu
- baptiste.laran@epitech.eu
- maxence.labourel@epitech.eu
