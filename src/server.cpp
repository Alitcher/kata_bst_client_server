#include "ServerModel.h"

int main() {
    ServerModel server;
    try {
        server.start();
        server.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}