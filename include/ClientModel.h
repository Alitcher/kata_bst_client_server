#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <string>

class ClientModel
{
public:
    ClientModel(const std::string& serverAddress, int port);
    ~ClientModel();

    bool connectToServer();
    std::string sendCommand(const std::string& command);
    void handleUserInput();

private:
    std::string serverAddress;
    int port;
    int clientSocket;

#ifdef _WIN32
    bool initializeWinsock();
    void cleanupWinsock();
#endif

    bool createSocket();
    bool connectToServerSocket();
    void closeSocket();
};

#endif  // CLIENTMODEL_H
