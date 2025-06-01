#include <iostream>
#include "../include/ClientTCP.h"

int main(int argc, char *argv[])
{
    TCPClient client("127.0.0.1", 8080);  // Указываем IP и порт сервера
    if (client.connectToServer()) {
        client.run();
    }
    return 0;
}
