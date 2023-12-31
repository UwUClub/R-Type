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
            * [Disconnect](#disconnect)
            * [Move](#move)
            * [Shoot](#shoot)

        * 3.2.2. [From server](#322-from-server)
            * [Player joined](#player-joined)
            * [Player left](#player-left)
            * [Player position update](#player-position-update)
            * [Player shot](#player-shot)
            * [Player got bonus](#player-got-bonus)
            * [Player died](#player-died)
            * [Enemy spawned](#enemy-spawned)
            * [Enemy died](#enemy-died)
            * [Enemy shot](#enemy-shot)
            * [Server is full](#server-is-full)

   * 3.3. [Reception Aknowledgment](#33-reception-aknowledgment)

   * 3.4. [Serialization](#34-serialization)

5. [Security Considerations](#4-security-considerations)
6. [Authors](#5-authors)

## 1. Introduction

The multiplayer R-Type game protocol is designed to enable communication
between clients and servers in a multiplayer R-Type game. This protocol
defines various message types and associated data structures for in-game
events, including player interactions and enemy behavior.

## 2. Definitions

### 2.1. Packet

The R-Type server accepts connections from UDP clients and communicates with them using packets. A packet is a sequence of bytes sent over the UDP connection.

### 2.2. Data Types

| Name | Size (bytes) | Encodes | Notes |
| - | - | - | - |
| boolean | 1 | Either false or true  | True is encoded as 0x01, false as 0x00 |
| unsigned byte | 1 | An integer between 0 and 255 | Unsigned 8-bit integer |
| unsigned short | 2 | An integer between 0 and 65535 | Unsigned 16-bit integer |
| float | 4 | A single-precision 32-bit IEEE 754 floating point number |
| string | ≥ 1 | A sequence of bytes representing characters |

## 3. Protocol Specification

Each client is a game player that listens to user inputs, sends actions to the server and calculates some game logic on its side. The server centralizes the main game logic and defines what happens in the game. It always has the last word on clients.

### 3.1. Packet Format

A packet has the following properties:
| Name | Kind | Description |
| - | - | - |
| `uuid` | 36-byte string | Unique id to identify the packet. See [part 3.3](#33-reception-aknowledgment) to learn about its utility |
| `type` | byte | [Packet type](#32-packet-types) |
| `payload` | depends on [packet type](#32-packet-types) | Data carried by the packet |

If the packet format is not respected, the server will send back a packet of Error type (see [packet types](#32-packet-types))

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
          <tr><td>unsigned byte</td></tr>
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

##### Player position update
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

##### Player shot
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
          <tr><td>Shooter entity ID</td></tr>
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
    <td><code>0x04</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Player entity ID</td></tr>
          <tr><td>Bonus type</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
          <tr><td>unsigned byte</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Player died
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
          <tr><td>Entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Enemy spawned
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
          <tr><td>Enemy entity ID</td></tr>
          <tr><td>Enemy horizontal position</td></tr>
          <tr><td>Enemy vertical position</td></tr>
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

##### Enemy died
<table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x07</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Enemy shot
 <table>
   <tr>
    <th>Type</th>
    <th>Bound to</th>
    <th>Payload description</th>
    <th>Payload type</th>
   </tr>
   <tr>
    <td><code>0x08</code></td>
    <td>Client</td>
    <td>
       <table>
          <tr><td>Shooter entity ID</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>unsigned short</td></tr>
       </table>
    </td>
   </tr>
</table>

##### Server is full
| Type | Bound to | Payload description | Payload type |
| - | - | - | - |
| `0x09` | Client | empty | empty |

#### 3.2.3. From client & server

##### Answer aknowledgment 
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-1` | Client & Server | empty | empty |

##### Answer error
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-2` | Client & Server | empty | empty |

The first packet sent by a client to its server **must** be of type [connect](#connect). Otherwise, the server will not listen to any of its packets.

When a client connects the server should:
   - send a [player joined](#player-joined) to the new player for each player already present in the server
   - send [enemy spawned](#enemy-spawned) packets to the connecting client, for each enemy already present in the server

This way the new client is aware of what is going during the gameplay.

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
