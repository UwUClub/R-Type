# Game Protocol for Multiplayer R-Type Game

*October 2023*

R-Type is an iconic series of horizontal-scrolling shoot 'em up video games developed by Irem, which began in 1987 in arcades. It is likely inspired by Konami's Gradius series, the first installment of which was released two years earlier.

## Table of Contents

1. [Introduction](#1-introduction)
2. [Definitions](#2-definitions)

   * 2.1. [Packet](#21-packet)

   * 2.2. [Data Types](#22-data-types)

3. [Protocol Specification](#3-protocol-specification)

   * 3.1. [Packet Format](#31-packet-format)

   * 3.2. [Packet Types](#32-packet-types)
   
        * 3.2.1. [From client](#321-from-client)
            * [Connect](#connect)
            * [Disonnect](#disconnect)
            * [Move](#move)
            * [Shoot](#shoot)

        * 3.2.2. [From server](#322-from-server)
            * [Player joined](#player-joined)
            * [Player left](#player-left)
            * [Player got bonus](#player-got-bonus)
            * [Monster spawned](#monster-spawned)
            * [Entity position update](#entity-position-update)
            * [Entity shot](#entity-shot)
            * [Entity died](#entity-died)
            * [Server is full](#server-is-full)

   * 3.3. [Reception Aknowledgment](#33-reception-aknowledgment)

   * 3.4. [Serialization](#34-serialization)

5. [Security Considerations](#4-security-considerations)
6. [Authors](#5-authors)

## 1. Introduction

The multiplayer R-Type game protocol is designed to enable communication
between clients and servers in a multiplayer R-Type game. This protocol
defines various message types and associated data structures for in-game
events, including player interactions and monster behavior.

## 2. Definitions

### 2.1. Packet

The R-Type server accepts connections from UDP clients and communicates with them using packets. A packet is a sequence of bytes sent over the UDP connection.

### 2.2. Data Types

| Name | Size (bytes) | Encodes |
| - | - | - |
| int | 4 | An integer between -2147483648 and 2147483647 |
| float | 4 | A floating point number |
| string | ≥ 1 | A sequence of bytes representing characters |

## 3. Protocol Specification

Each client is a game player that listens to user inputs, sends actions to the server and calculates some game logic on its side. The server centralizes the main game logic and defines what happens in the game. It always has the last word on clients.

### 3.1. Packet Format

A packet has the following properties:
| Name | Kind | Description |
| - | - | - |
| `uuid` | 36-byte string | Unique id to identify the packet. See [part 2.3](#23-reception-aknowledgment) to learn about its utility |
| `type` | 4-byte int | Packet type. See [part 2.2](#22-packet-type) to get the list of packet types |
| `payload` | vector of float (variable size) | Data carried by the packet. The size and meaning of each value depends on packet type, check [part 2.2](#22-packet-type) |

If the packet format is not respected, the packet will be ignored by the server.

### 3.2. Packet Types

#### 3.2.1. From client

##### Connect
| Type | Bounds to | Payload description | Payload type |
| - | - | - | - |
| `0x00` | Server | empty | empty |

##### Disconnect
| Type | Bounds to | Payload description | Payload type |
| - | - | - | - |
| `0x01` | Server | empty | empty |

##### Move
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x02</code></td>
    <td>Server</td>
    <td>
       <table>
          <tr><td>Move shift on horizontal axis</td></tr>
          <tr><td>Move shift on vertical axis</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>float</td></tr>
          <tr><td>float</td></tr>
       </table>
    </td>
   </tr>
</table> 

##### Shoot
| Type | Bounds to | Payload description | Payload type |
| - | - | - | - |
| `0x03` | Server | empty | empty |

#### 3.2.2. From server

##### Player joined
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x00</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Player entity ID</td></tr>
          <tr><td>Is receiver the concerned player</td></tr>
          <tr><td>Player color</td></tr>
          <tr><td>Player horizontal position</td></tr>
          <tr><td>Player vertical position</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
          <tr><td>boolean</td></tr>
          <tr><td>color</td></tr>
          <tr><td>float</td></tr>
          <tr><td>float</td></tr>
       </table>
    </td>
   </tr>
</table> 

##### Player left
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x01</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Player entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Player got bonus
<table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x02</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Player entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>bonus</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Monster spawned
<table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x03</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Monster entity ID</td></tr>
          <tr><td>Monster horizontal position</td></tr>
          <tr><td>Monster vertical position</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>bonus</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Entity position update
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x04</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Entity ID</td></tr>
          <tr><td>Entity horizontal position</td></tr>
          <tr><td>Entity vertical position</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
          <tr><td>float</td></tr>
          <tr><td>float</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Entity shot
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x05</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Player entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Entity died
<table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x06</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>bonus</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Server is full
| Type | Bound to | Payload description | Payload type |
| - | - | - | - |
| `0x07` | Client | empty | empty |

#### 3.2.3. From client & server

##### Answer aknowledgment 
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-1` | Client & Server | empty | empty |

##### Answer error
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-2` | Client & Server | empty | empty |

The first packet sent by a client to its server **must** be of type [connect](#3211-connect). Otherwise, the server will not listen to any of its packets.

When a client connects the server should:
   - send `PLAYER_SPAWN` packets to the connecting client, for each player already present in the server
   - send `ENEMY_SPAWN` packets to the connecting client, for each enemy already present in the server

This way the connecting client is aware of what is going during the gameplay.

### 3.3. Reception Aknowledgment

A client or server receiving a packet whose type is `>= 0` must send back an aknowledgment packet (type `-1`). Its uuid must be the same as the one of the received packet. This practice is recommended for timeout and crash detection: not sending aknowledgment results to be considered as inactive and kicked by the server or left by the client.

### 3.4. Serialization

The protocol is binary, so packets must be serialized to binary format before being sent. It must be unserialized from binary format before being read. 

## 4. Security Considerations

Implementations of this protocol should consider security aspects to protect against unauthorized access, cheating, and other potential vulnerabilities.

You must check your packet reception when making a client or server: always make sure the payload size and values are valid.

Remember that the server should always have the last word on the client.

## 5. Authors

**A game developed by:**
- Valentin GEGOUX (valentin.gegoux@epitech.eu)
- Mathéo MARTIN (matheo.martin@epitech.eu)
- Baptiste LARAN (baptiste.laran@epitech.eu)
- Maxence LABOUREL (maxence.labourel@epitech.eu)

*Epitech Toulouse, promo 2026*

## Copyright Notice

Copyright (c) The persons identified as the game developers.  All rights reserved.
