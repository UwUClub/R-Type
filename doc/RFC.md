# Game Protocol for Multiplayer R-Type Game

*October 2023*

R-Type is an iconic series of horizontal-scrolling shoot 'em up video games developed by Irem, which began in 1987 in arcades. It is likely inspired by Konami's Gradius series, the first installment of which was released two years earlier.

## Table of Contents

1. [Introduction](#1-introduction)
2. [Protocol Specification](#2-protocol-specification)

   2.1. [Packet Format](#21-packet-format)

   2.2. [Packet Type](#22-packet-type)

   2.3. [Reception Aknowledgment](#23-reception-aknowledgment)

   2.4. [Serialization](#24-serialization)

3. [Security Considerations](#3-security-considerations)
4. [Authors](#4-authors)

## 1. Introduction

The multiplayer R-Type game protocol is designed to enable communication
between clients and servers in a multiplayer R-Type game. This protocol
defines various message types and associated data structures for in-game
events, including player interactions and monster behavior.

## 2. Protocol Specification

Each client is a game player that listens to user inputs, sends actions to the server and calculates some game logic on its side. The server centralizes the main game logic and defines what happens in the game. It always has the last word on clients.

### 2.1. Packet Format

A packet has the following properties:
| Name | Kind | Description |
| - | - | - |
| `uuid` | 36-byte string | Unique id to identify the packet. See [part 2.3](#23-reception-aknowledgment) to learn about its utility |
| `type` | 4-byte int | Packet type. See [part 2.2](#22-packet-type) to get the list of packet types |
| `payload` | vector of float (variable size) | Data carried by the packet. The size and meaning of each value depends on packet type, check [part 2.2](#22-packet-type) |

If the packet format is not respected, the packet will be ignored by the server.

### 2.2 Packet Type

Packets sent by client:

| Name | Type | Bounds to | Payload format | Payload size |
| - | - | - | - | - |
| `CONNECT` | `0` | Server | empty | 0 bytes |
| `DISCONNECT` | `1` | Server | empty | 0 bytes |
| `MOVE` | `3` | Server | <ol><li>Move shift on horizontal axis (negative being left, positive being right, max absolute value is 1)</li><li>Move shift on vertical axis (negative being bottom, positive being top, max absolute value is 1)</li></ol> | 8 bytes |
| `SHOOT` | `4` | Server | empty | 0 bytes |
| `BONUS` | `5` | Server | <ol><li>Bonus type</li></ol> | 4 bytes

Packets sent by server:

| Name | Type | Bounds to | Payload format | Payload size |
| - | - | - | - | - |
| `PLAYER_SPAWN` | `0` | Client | <ol><li>Entity id</li><li>Is packet receiver the concerned player (`1` for yes, otherwise no)</li><li>Player color (goes from `0` to `3`)</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> | 20 bytes |
| `PLAYER_DISCONNECTION` | `1` | Client | <ol><li>Id of the entity who leaves</li></ol> | 4 bytes |
| `PLAYER_POSITION` | `2` | Client | <ol><li>Entity id</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> | 12 bytes |
| `PLAYER_SHOOT` | `3` | Client | <ol><li>Shooting entity id</li></ol> | 4 bytes |
| `PLAYER_BONUS` | `4` | Client | <ol><li>Concerned entity id</li></ol> | 4 bytes |
| `PLAYER_DEATH` | `5` | Client | <ol><li>Dying entity id</li></ol> | 4 bytes |
| `ENEMY_SPAWN` | `6` | Client | <ol><li>Spawning entity id</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> | 12 bytes |
| `ENEMY_DEATH` | `7` | Client | <ol><li>Dying entity id</li></ol> | 4 bytes |
| `ENEMY_SHOOT` | `8` | Client | <ol><li>Shooting entity id</li></ol> | 4 bytes |
| `SERVER_FULL` | `9` | Client | empty | 0 bytes |

Packets sent by both:

| Name | Type | Bounds to | Payload format | Payload size |
| - | - | - | - | - |
| `RECEPTION_AKNOWLEDGMENT` | `-1` | Client & Server | empty | 0 bytes |

The first packet sent by a client to its server **must** be of type `CONNECT`. Otherwise, the server will not listen to any of its packets.

When a client connects the server should:
   - send `PLAYER_SPAWN` packets to the connecting client, for each player already present in the server
   - send `ENEMY_SPAWN` packets to the connecting client, for each enemy already present in the server

This way the connecting client is aware of what is going during the gameplay.

### 2.3. Reception Aknowledgment

A client or server receiving a packet whose type is `>= 0` must send back an aknowledgment packet (type `-1`). Its uuid must be the same as the one of the received packet. This practice is recommended for timeout and crash detection: not sending aknowledgment results to be considered as inactive and kicked by the server or left by the client.

### 2.4. Serialization

The protocol is binary, so packets must be serialized to binary format before being sent. It must be unserialized from binary format before being read.

## 3. Security Considerations

Implementations of this protocol should consider security aspects to protect against unauthorized access, cheating, and other potential vulnerabilities.

You must check your packet reception when making a client or server: always make sure the payload size and values are valid.

Remember that the server should always have the last word on the client.

## 4. Authors

**A game developed by:**
- Valentin GEGOUX (valentin.gegoux@epitech.eu)
- Mathéo MARTIN (matheo.martin@epitech.eu)
- Baptiste LARAN (baptiste.laran@epitech.eu)
- Maxence LABOUREL (maxence.labourel@epitech.eu)

*Epitech Toulouse, promo 2026*

## Copyright Notice

Copyright (c) The persons identified as the game developers.  All rights reserved.
