#include <iostream>
#ifdef _WIN32
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define close closesocket
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddress;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return 1;
    }
#endif

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
#ifdef _WIN32
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
    serverAddress.sin_addr.s_addr = INADDR_ANY;

#endif
    serverAddress.sin_port = htons(8888);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::cout << "Connected to server. You can start entering commands..." << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        if (send(clientSocket, command.c_str(), command.length(), 0) == -1)
        {
            std::cerr << "Failed to send command to server" << std::endl;
            break;
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
            break;
        }

        std::string response(buffer);
        std::cout << response << std::endl;
    }

    close(clientSocket);
    return 0;
}
