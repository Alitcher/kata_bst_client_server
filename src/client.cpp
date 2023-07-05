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

const std::string serverAddress = "127.0.0.1";
const int defaultPort = 8888;

// Function to establish the connection with the server
int connectToServer(const std::string &serverAddress, int port)
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in serverAddr
    {
    };
    serverAddr.sin_family = AF_INET;
#ifdef _WIN32
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());
#else
    serverAddr.sin_addr.s_addr = INADDR_ANY;
#endif
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        close(clientSocket);
        return -1;
    }

    return clientSocket;
}

// Function to send a command to the server and receive the response
std::string sendCommand(int &clientSocket, const std::string &command)
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

// Function to handle user input and interaction
void handleUserInput(int &clientSocket)
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

        std::string response = sendCommand(clientSocket, command);
        std::cout << response << std::endl;
    }
}

int main()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return 1;
    }
#endif

    int clientSocket = connectToServer(serverAddress, defaultPort);
    if (clientSocket == -1)
    {
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    handleUserInput(clientSocket);

    close(clientSocket);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
