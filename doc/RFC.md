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

1. [Introduction](#1-introduction)
2. [Protocol Specification](#2-protocol-specification)

   2.1. [Packet Format](#21-packet-format)

   2.2. [Packet Type](#22-packet-type)

   2.3. [Reception Aknowledgment](#23-reception-aknowledgment)

   2.4. [Serialization](#24-serialization)

3. [Security Considerations](#3-security-considerations)
4. [Author's Addresses](#4-authors-addresses)

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
| `uuid` | 16-byte string | Unique id to identify the packet. See [part 2.3](#23-reception-aknowledgment) to learn about its utility |
| `type` | 4-byte int | Packet type. See [part 2.2](#22-packet-type) to get the list of packet types |
| `payload` | vector of float | Data carried by the packet. The size and meaning of each value depends on packet type, check [part 2.2](#22-packet-type) |

### 2.2 Packet Type

Packets sent by client:

| Name | Type | Bounds to | Payload format |
| - | - | - | - |
| `CONNECT` | `0` | Server | empty |
| `DISCONNECT` | `1` | Server | empty |
| `MOVE` | `2` | Server | <ol><li>Move shift on horizontal axis (negative being left, positive being right, max absolute value is 1)</li><li>Move shift on vertical axis (negative being bottom, positive being top, max absolute value is 1)</li></ol> |
| `SHOOT` | `3` | Server | empty |

Packets sent by server:

| Name | Type | Bounds to | Payload format |
| - | - | - | - |
| `PLAYER_SPAWN` | `0` | Client | <ol><li>Entity id</li><li>Is packet receiver the concerned player (`1` for yes, otherwise no)</li><li>Player color (goes from `0` to `3`)</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> |
| `PLAYER_DISCONNECTION` | `1` | Client | <ol><li>Id of the entity who leaves</li></ol> |
| `PLAYER_POSITION` | `2` | Client | <ol><li>Entity id</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> |
| `PLAYER_SHOOT` | `3` | Client | <ol><li>Shooting entity id</li></ol> |
| `PLAYER_DEATH` | `4` | Client | <ol><li>Dying entity id</li></ol> |
| `ENEMY_SPAWN` | `5` | Client | <ol><li>Spawning entity id</li><li>Entity horizontal position</li><li>Entity vertical position</li></ol> |
| `ENEMY_SHOOT` | `6` | Client | <ol><li>Shooting entity id</li></ol> |
| `ENEMY_DEATH` | `7` | Client | <ol><li>Dying entity id</li></ol> |

Packets sent by both:

| Name | Type | Bounds to | Payload format |
| - | - | - | - |
| `RECEPTION_AKNOWLEDGMENT` | `-1` | Client & Server | empty |

The first packet sent by a client to its server **must** be of type `CONNECT`. Otherwise, the server will not listen to any of its packets.

When a client connects the server should:
   - send `PLAYER_SPAWN` packets to the connecting client, for each player already present in the server
   - send `ENEMY_SPAWN` packets to the connecting client, for each enemy already present in the server

This way the connecting client is aware of what is going during the gameplay.

### 2.3. Reception Aknowledgment

A client or server receiving a packet whose type is `>= 0` must send back an aknowledgment packet (type `-1`). Its uuid must be the same as the one of the received packet.

### 2.4. Serialization

The protocol is binary, so packets must be serialized to binary format before being sent. It must be unserialized from binary format before being read.

## 3. Security Considerations

Implementations of this protocol should consider security aspects to protect against unauthorized access, cheating, and other potential vulnerabilities.

Remember that the server should always have the last word on the client.

## 4. Author's Addresses

Our email addresses:
- valentin.gegoux@epitech.eu
- matheo.martin@epitech.eu
- baptiste.laran@epitech.eu
- maxence.labourel@epitech.eu
