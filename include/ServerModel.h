#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "BST.h"
#include <string>
#include <sstream>
#include <iostream>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netinet/in.h>
#endif

class ServerModel {
    BST bst;
    int serverSocket;
    int clientSocket;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength;
public:
    ServerModel();
    ~ServerModel();
    void start();
    void run();
    std::string processCommand(const std::string& command);
};

#endif
