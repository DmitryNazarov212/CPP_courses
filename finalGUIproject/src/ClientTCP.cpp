#include "../include/ClientTCP.h"
#include <iostream>
#include <cstring>

TCPClient::TCPClient(const std::string& serverIp, int port)
    : _serverIp(serverIp), _port(port), _socket(-1) {
}

bool TCPClient::connectToServer() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        std::cerr << "Socket creation failed: " << errno << std::endl;
        logger.log("Socket creation failed: " + std::to_string(errno));
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);

    if (inet_pton(AF_INET, _serverIp.c_str(), &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported: " << errno << std::endl;
        logger.log("Invalid address/Address not supported: " + std::to_string(errno));
        close(_socket);
        return false;
    }

    if (connect(_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Connection failed: " << errno << std::endl;
        logger.log("Connection failed: " + std::to_string(errno));
        close(_socket);
        return false;
    }

    std::cout << "Connected to the server!" << std::endl;
    logger.log("Connected to the server at " + _serverIp + ":" + std::to_string(_port));
    return true;
}

void TCPClient::sendMessage(const std::string& message) {
    logger.log("You: " + message); // Log sent message
    if (send(_socket, message.c_str(), message.length(), 0) == -1) {
        std::cerr << "Message send failed: " << errno << std::endl;
        logger.log("Message send failed: " + std::to_string(errno));
    }
    else {
        std::cout << "Message sent: " << message << std::endl;
    }
}

void TCPClient::receiveMessage() {
    char buffer[1024];
    ssize_t bytesReceived = recv(_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::string receivedMessage(buffer);
        logger.log("Server: " + receivedMessage); // Log received message
        std::cout << "Received: " << receivedMessage << std::endl;
    }
    else if (bytesReceived == 0) {
        std::cout << "Connection closed by server." << std::endl;
        logger.log("Connection closed by server.");
    }
    else {
        std::cerr << "Failed to receive message: " << errno << std::endl;
        logger.log("Failed to receive message: " + std::to_string(errno));
    }
}

void TCPClient::run() {
    std::string message;
    while (true) {
        // Проверяем соединение перед отправкой
        char testBuffer[1];
        ssize_t testResult = recv(_socket, testBuffer, sizeof(testBuffer), MSG_PEEK);
        if (testResult <= 0) {
            if (errno != EWOULDBLOCK) {
                std::cout << "Server disconnected" << std::endl;
                break;
            }
        }
        
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);
        if (message == "exit") {
            break;
        }
        sendMessage(message);
        receiveMessage();
    }
    close(_socket);
    logger.log("Client disconnected from server.");
}
