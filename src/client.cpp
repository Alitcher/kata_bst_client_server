#include "ClientModel.h"

int main()
{
    const std::string serverAddress = "127.0.0.1";
    const int defaultPort = 8888;

    ClientModel clientModel(serverAddress, defaultPort);

    if (!clientModel.connectToServer())
    {
        return 1;
    }

    clientModel.handleUserInput();

    return 0;
}
