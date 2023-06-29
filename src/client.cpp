#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8888);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::cout << "Connected to server. You can start entering commands..." << std::endl;

    while (true) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        if (send(clientSocket, command.c_str(), command.length(), 0) == -1) {
            std::cerr << "Failed to send command to server" << std::endl;
            break;
        }

        char buffer[1024] = {0};
        int bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            std::cerr << "Failed to read response from server" << std::endl;
            break;
        }

        std::string response(buffer);
        std::cout << response << std::endl;
    }

    close(clientSocket);
    return 0;
}
