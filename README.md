# SocketMaster

SocketMaster is a WebSocket server designed to provide a fast, scalable, and robust solution for managing multiple WebSocket endpoints efficiently. It introduces a unique architecture where clients connect to a single, scalable WebSocket endpoint using a unique socket name. SocketMaster then intelligently routes incoming connections to the appropriate WebSocket endpoint based on the provided socket name, enabling seamless communication between clients and endpoints.

## Key Features
- Single, Self-healing WebSocket Endpoint: Consolidate multiple WebSocket endpoints into a single, scalable server instance. All this requires is setting up your application to perform one additional 'SocketMaster Handshake' in addition to the regular TCP and HTTP handshakes that are typically executed when a websocket connection is instated. 
- Dynamic Routing: Intelligently route incoming connections to the appropriate WebSocket endpoint based on the provided socket name.
- Persistent Connection Management: Auto-restart and recover from errors or disconnections gracefully, ensuring continuous operation of WebSocket endpoints.
- Parallelised and Multithreaded Processing: Handle incoming connections concurrently across multiple threads and workers, enabling optimal performance and scalability.

## Architecture Overview

At its core, SocketMaster operates as a centralized WebSocket endpoint manager. It abstracts the complexity of managing multiple WebSocket endpoints by consolidating them into a single, scalable server instance. This architecture offers several advantages:

### 1. Single Scalable WebSocket Endpoint

SocketMaster acts as a gateway for all WebSocket connections, allowing clients to connect to a single endpoint regardless of the underlying WebSocket endpoint's location or purpose. This simplifies the client connection process and enhances system manageability.

### 2. Dynamic Routing Mechanism

During the WebSocket connection establishment process, SocketMaster utilizes a unique routing handshake mechanism. When a client connects to SocketMaster, it provides a socket name as part of the handshake. SocketMaster then uses this socket name to determine the appropriate WebSocket endpoint to route the connection to. This dynamic routing mechanism ensures efficient utilization of server resources and enables seamless communication between clients and endpoints.

### 3. Persistent Connection Management

SocketMaster implements persistent connection management to ensure continuous operation of WebSocket endpoints. In the event of a connection failure or disconnection, SocketMaster automatically restarts the affected WebSocket endpoint, minimizing downtime and enhancing system reliability.

### 4. Parallelized and Multithreaded Processing

To achieve high performance and scalability, SocketMaster leverages parallelized and multithreaded processing techniques. Incoming connections are handled concurrently across multiple threads, maximizing throughput and reducing latency. This parallelized processing ensures optimal resource utilization and enables SocketMaster to scale effectively with increasing workload demands.

## Installation & Setup

### Requirements
- C++ compiler with C++17 support
- Boost.Asio library and Boost.Program_options library (``sudo apt install libboost-all-dev``)
- Google's Abseil library installed for C++ and available to CMake
- If SocketMaster requires contact with the outside world, you need to do all of the required typical port forwarding and DNS setup on your machine that you'd do for an HTTP server

### Installation

1. Clone the SocketMaster repository:

``git clone https://github.com/yourusername/SocketMaster.git``

Build the project:

```
cd SocketMaster
mkdir build
cd build
cmake ..
make
```

### Configuration

SocketMaster is easy to use. All it requires is that on startup, you supply a configuration file (``config.ini``) specifying the WebSocket endpoints and their corresponding socket names/purposes. These names/purposes are used in the routing process. An example ``config.ini`` file might look like this:

```
[Endpoint1]
Name = endpoint1
Port = 8080

[Endpoint2]
Name = endpoint2
Port = 9090
Usage
Start SocketMaster with the specified configuration file:
```

You can supply the configuration file to socket master through the ``--config`` flag:
```
./socketmaster --config config.ini
```

## Socket Client Usage

Connect clients to SocketMaster using the ONE websocket address that SocketMaster provides you. Upon connection, the client must perform a 'SocketMaster' handshake. Note that the client must contain a file, map, or some kind of data structure that keeps track of all the websocket routes/names that it expects to use during the program lifecycle. This might be in a file like ``expected_configuration.txt``, some JSON file, or even a string. The contents of such a file may look like this:

```
Endpoint1
Endpoint2
Endpoint3
```

This is the only change that needs to be made in order to support SocketMaster versus your traditional websocket system. In the first message after connecting to the SocketMaster endpoint, the client/server will communicate as follows:

1. Client: ``{event: SMHandshake, data: SYN}``
2. SocketMaster: ``{event: SMHandshake, data: SYN/ACK}``
3. Client: ``{event: SMHandshake, data: ACK}``
4. Client: For each route-name ``x`` specified in ``LINES(expected_configuration.txt)``, send: ``{event: SMHandshake, data: x}``
5. Server: For each message received with format ``{event: SMHandshake, data: x}``, respond with 'ACK'
6. Client: Communicate the end of the handshake with a final message where ``event: SMHandshakeEnd``
7. Server: Server ACK's response and is ready to accept any socket connection from any of the routes specified in ``LINES(expected_configuration.txt)`` OR any route specified in its server-side portmap file, ``config.ini``

Then, all socket messages can be sent to the single SocketMaster endpoint with just an extra header containing ``ROUTENAME=<desired socket route name/purpose>``. E.g., the header may include ``ROUTENAME=Endpoint1``. As you can see, the only trade-off is the extra steps required in connecting to the client.
