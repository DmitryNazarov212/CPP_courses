#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>
#include <netinet/in.h> // POSIX socket headers for Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../include/Logger.h" // Logger for logging messages

class TCPClient {
public:
    TCPClient(const std::string& serverIp, int port);
    bool connectToServer();
    void sendMessage(const std::string& message);
    void receiveMessage();
    void run();

private:
    std::string _serverIp;
    int _port;
    int _socket;
    Logger logger; // Logger instance
};

#endif // TCPCLIENT_H
