# Networked BST

👋 Welcome to the Networked Data Structure project! This is a simple networked application implemented in C++20 that allows two programs to communicate with each other using sockets. The application consists of a server program and a client program.

## Getting Started

To run the program, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Build the project using the provided Makefile by running the command `make all`.
4. Start the server by running the command `./server`.
5. Open another terminal window and start the client by running the command `./client`.
6. You can now enter commands in the client terminal and see the responses from the server.

## Project Architecture

The project is organized into several components:

- `BST`: Represents the Binary Search Tree data structure, which is responsible for storing and managing integers.
- `Node`: Represents a node in the Binary Search Tree.
- `ServerModel`: Implements the server-side functionality, including socket creation, command processing, and communication with the client.
- `Client`: Implements the client-side functionality, including command input, sending commands to the server, and displaying server responses.

## Multithreaded Version

A high-level explanation of how it can be implemented:

- Server: The server can be modified to use a multi-threaded approach. After accepting a new client connection, a new thread can be instantiated to handle the communication with that client. This allows the server to handle multiple client connections simultaneously.
- Client: The client can keep being single-threaded as it initiates the connection with the server and sends commands sequentially.

The project, however, does not have multithreading implemented. This explanation gives you an idea of how it could be done.

Enjoy!

