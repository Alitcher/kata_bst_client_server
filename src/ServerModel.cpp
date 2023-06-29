#include "ServerModel.h"

ServerModel::ServerModel()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    // Enable the socket to reuse the address
    int optval = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        throw std::runtime_error("Failed to set socket options");
    }
}

ServerModel::~ServerModel()
{
    close(clientSocket);
    close(serverSocket);
}

void ServerModel::start()
{
    int portNumber = 8888;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNumber);
    clientAddressLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(serverSocket, 5) == -1)
    {
        throw std::runtime_error("Failed to listen");
    }

    std::cout << "Server started. Listening for connections at port: " << portNumber << std::endl;

    while (true)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (clientSocket == -1)
        {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        std::cout << "Client connected" << std::endl;

        run();
    }
}

void ServerModel::run()
{
    while (true)
    {
        char buffer[1024] = {0};
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1)
        {
            std::cerr << "Failed to read from socket" << std::endl;
            break;
        }
        else if (bytesRead == 0)
        {
            std::cout << "Client disconnected" << std::endl;
            break;
        }

        std::string command(buffer);
        std::string response = processCommand(command);
        if (send(clientSocket, response.c_str(), response.length(), 0) == -1)
        {
            std::cerr << "Failed to send response to client" << std::endl;
            break;
        }
    }
}
std::string ServerModel::processCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string operation;
    int number;

    iss >> operation;
    if (!(iss >> number))
    {
        return "Invalid command, expected number after operation";
    }

    if (operation == "insert")
    {
        if (!bst.find(number))
        {
            bst.insert(number);
            return "Inserted " + std::to_string(number) + " successfully!";
        }
        else
        {
            return "ERROR: " + std::to_string(number) + " already exists in BST";
        }
    }
    else if (operation == "delete")
    {
        if (bst.find(number))
        {
            bst.remove(number);
            return "Deleted " + std::to_string(number) + " successfully!";
        }
        else
        {
            return "ERROR: " + std::to_string(number) + " does not exist in BST";
        }
    }
    else if (operation == "find")
    {
        if (bst.find(number))
        {
            return "Found " + std::to_string(number);
        }
        else
        {
            return "Not found " + std::to_string(number);
        }
    }
    else
    {
        return "Invalid command";
    }
}