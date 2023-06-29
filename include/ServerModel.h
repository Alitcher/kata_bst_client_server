#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "BST.h"
#include <string>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

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
