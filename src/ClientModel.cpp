#include "ClientModel.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define close closesocket
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

ClientModel::ClientModel(const std::string& serverAddress, int port)
    : serverAddress(serverAddress), port(port), clientSocket(-1)
{
}

ClientModel::~ClientModel()
{
    closeSocket();

#ifdef _WIN32
    cleanupWinsock();
#endif
}

#ifdef _WIN32
bool ClientModel::initializeWinsock()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return false;
    }
    return true;
}

void ClientModel::cleanupWinsock()
{
    WSACleanup();
}
#endif

bool ClientModel::createSocket()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    return true;
}

bool ClientModel::connectToServerSocket()
{
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
#ifdef _WIN32
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());
#else
    serverAddr.sin_addr.s_addr = INADDR_ANY;
#endif
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        closeSocket();
        return false;
    }
    return true;
}

bool ClientModel::connectToServer()
{
#ifdef _WIN32
    if (!initializeWinsock())
    {
        return false;
    }
#endif

    if (!createSocket())
    {
#ifdef _WIN32
        cleanupWinsock();
#endif
        return false;
    }

    if (!connectToServerSocket())
    {
        closeSocket();
#ifdef _WIN32
        cleanupWinsock();
#endif
        return false;
    }

    return true;
}

void ClientModel::closeSocket()
{
    if (clientSocket != -1)
    {
        close(clientSocket);
        clientSocket = -1;
    }
}

std::string ClientModel::sendCommand(const std::string& command)
{
    if (send(clientSocket, command.c_str(), command.length(), 0) == -1)
    {
        std::cerr << "Failed to send command to server" << std::endl;
        return "";
    }

    char buffer[1024] = {0};

   int bytesRead = -1;
#ifdef _WIN32
    bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
#else
    bytesRead = read(clientSocket, buffer, sizeof(buffer));
#endif
    if (bytesRead == -1)
    {
        std::cerr << "Failed to read response from server" << std::endl;
        return "";
    }

    std::string response(buffer);
    return response;
}

void ClientModel::handleUserInput()
{
    std::cout << "Connected to server. You can start entering commands..." << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        if (command == "exit")
        {
            break;
        }

        std::string response = sendCommand(command);
        std::cout << response << std::endl;
    }
}
