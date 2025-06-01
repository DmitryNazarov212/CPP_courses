#include "../include/ServerTCP.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <fstream>
#include "../include/DataBase.h"

TCPServer::TCPServer(int port, QObject *parent)
    : QObject(parent), _port(port), _serverSocket(-1), running(false) {
}

bool TCPServer::start() {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        std::cerr << "Socket creation failed: " << errno << std::endl;
        logger.log("Socket creation failed: " + std::to_string(errno));
        return false;
    }

    // Allow address reuse to avoid "Address already in use" errors
    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "Setsockopt failed: " << errno << std::endl;
        logger.log("Setsockopt failed: " + std::to_string(errno));
        close(_serverSocket);
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(_port);

    if (bind(_serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Binding failed: " << errno << std::endl;
        logger.log("Binding failed: " + std::to_string(errno));
        close(_serverSocket);
        return false;
    }

    if (listen(_serverSocket, 5) == -1) {
        std::cerr << "Listen failed: " << errno << std::endl;
        logger.log("Listen failed: " + std::to_string(errno));
        close(_serverSocket);
        return false;
    }

    running = true;
    std::cout << "Server started on port " << _port << ", waiting for clients..." << std::endl;
    logger.log("Server started on port " + std::to_string(_port));
    
    // Запускаем поток для приема клиентов
    std::thread(&TCPServer::acceptClients, this).detach();
    
    emit userListUpdated();
    return true;

}

void TCPServer::acceptClients() {
    while (running) {
        sockaddr_in clientAddress;
        socklen_t clientLen = sizeof(clientAddress);
        int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
        if (clientSocket == -1) {
            if (running) {
                std::cerr << "Client connection failed: " << errno << std::endl;
                logger.log("Client connection failed: " + std::to_string(errno));
            }
            continue;
        }
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, INET_ADDRSTRLEN);
        std::string ipAddress = clientIP;

        std::cout << "Client connected from " << ipAddress << std::endl;
        logger.log("Client connected from " + ipAddress);


        ConnectedUser user;
        user.ipAddress = ipAddress;
        user.socket = clientSocket;
        user.status = "Connected";
        std::lock_guard<std::mutex> lock(mutex);
        connectedUsers[clientSocket] = user;

        emit userListUpdated(); // Notify UI of new client
        std::thread(&TCPServer::handleClient, this, clientSocket).detach();
    }
}

void TCPServer::handleClient(int clientSocket) {
    DataBase db;
    char buffer[1024];
    bool loggedIn = false;
    std::string username;

    while (running) {
        if (!loggedIn) {
            send(clientSocket, "1. Register\n2. Login\n", 22, 0);
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                std::cerr << "Client disconnected or error occurred: " << errno << std::endl;
                logger.log("Client disconnected or error: " + std::to_string(errno));
                break;
            }

            std::string input(buffer);
            input.erase(input.find_last_not_of(" \n\r\t") + 1);

            int choice = 0;
            try {
                choice = std::stoi(input);
            }
            catch (const std::exception& e) {
                send(clientSocket, "Invalid input. Please enter a number.\n", 36, 0);
                continue;
            }

            if (choice == 1) {
                send(clientSocket, "Enter username: ", 17, 0);
                memset(buffer, 0, sizeof(buffer));
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) break;
                username = std::string(buffer, bytesReceived);
                username.erase(username.find_last_not_of(" \n\r\t") + 1);

                send(clientSocket, "Enter password: ", 17, 0);
                memset(buffer, 0, sizeof(buffer));
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) break;
                std::string password = std::string(buffer, bytesReceived);
                password.erase(password.find_last_not_of(" \n\r\t") + 1);
                
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    auto it = std::find(bannedUsers.begin(), bannedUsers.end(), username);
                    if (it != bannedUsers.end()) {
                        send(clientSocket, "You are banned!\n", 16, 0);
                        logger.log("Banned user attempted registration: " + username);
                        continue;
                    }
                    
                    if (db.registerUser(username, password)) {
                        send(clientSocket, "Registration successful! Please log in.\n", 40, 0);
                        logger.log("User registered: " + username);
                    }
                    else {
                        send(clientSocket, "Registration failed. Try again.\n", 32, 0);
                        logger.log("Registration failed for user: " + username);
                    }
                }
            }
            else if (choice == 2) {
                send(clientSocket, "Enter username: ", 17, 0);
                memset(buffer, 0, sizeof(buffer));
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) break;
                username = std::string(buffer, bytesReceived);
                username.erase(username.find_last_not_of(" \n\r\t") + 1);

                send(clientSocket, "Enter password: ", 17, 0);
                memset(buffer, 0, sizeof(buffer));
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) break;
                std::string password = std::string(buffer, bytesReceived);
                password.erase(password.find_last_not_of(" \n\r\t") + 1);
                
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    auto it = std::find(bannedUsers.begin(), bannedUsers.end(), username);
                    if (it != bannedUsers.end()) {
                        send(clientSocket, "You are banned!\n", 16, 0);
                        logger.log("Banned user attempted login: " + username);
                        continue;
                    }

                    if (db.authenticateUser(username, password)) {
                        connectedUsers[clientSocket].username = username;
                        connectedUsers[clientSocket].status = "Logged in";
                        send(clientSocket, "Login successful.\n", 18, 0);
                        logger.log("User logged in: " + username);
                        emit userListUpdated();
                        emit newMessage(QString::fromStdString(username + " has logged in."));
                        loggedIn = true;
                    }
                    else {
                        send(clientSocket, "Incorrect credentials. Please try again.\n", 41, 0);
                        logger.log("Failed login attempt for user: " + username);
                    }
                }
            }
            else {
                send(clientSocket, "Invalid choice. Please try again.\n", 32, 0);
            }
        }
        else {
            send(clientSocket, "1. Send message to chat\n2. Log out\n", 35, 0);
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                std::cerr << "Client disconnected or error occurred: " << errno << std::endl;
                logger.log("Client disconnected or error: " + std::to_string(errno));
                break;
            }

            std::string input(buffer);
            input.erase(input.find_last_not_of(" \n\r\t") + 1);

            int action = 0;
            try {
                action = std::stoi(input);
            }
            catch (const std::exception& e) {
                send(clientSocket, "Invalid input. Please enter a number.\n", 36, 0);
                continue;
            }

            if (action == 1) {
                send(clientSocket, "Enter message for chat: ", 24, 0);
                memset(buffer, 0, sizeof(buffer));
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) break;
                std::string message = std::string(buffer, bytesReceived);
                message.erase(message.find_last_not_of(" \n\r\t") + 1);

                std::string fullMessage = username + ": " + message;
                sendToAllClients(fullMessage);
                emit newMessage(QString::fromStdString(fullMessage));
            }
            else if (action == 2) {
                send(clientSocket, "Logging out.\n", 13, 0);
                logger.log("User logged out: " + username);
                emit newMessage(QString::fromStdString(username + " has logged out."));
                break;
            }
            else {
                send(clientSocket, "Invalid action. Please try again.\n", 32, 0);
            }
        }
    }

    close(clientSocket);
    if (!username.empty()) {
        connectedUsers.erase(clientSocket);
        emit userListUpdated();
        std::cout << "Client disconnected: " << username << std::endl;
        logger.log("Client disconnected: " + username);
    }
}

void TCPServer::sendToAllClients(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    logger.log(message);
    emit newMessage(QString::fromStdString(message)); // Notify UI
    for (const auto& client : connectedUsers) {
        send(client.first, message.c_str(), message.length(), 0);
    }
}

void TCPServer::stopServer() {
    running = false;
    for (const auto& client : connectedUsers) {
        close(client.first);
    }
    connectedUsers.clear();
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }
    std::cout << "Server stopped." << std::endl;
    logger.log("Server stopped");
    emit userListUpdated(); // Notify UI of server stop
}

void TCPServer::kickUser(const std::string& username) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto it = connectedUsers.begin(); it != connectedUsers.end(); ++it) {
        if (it->second.username == username) {
            send(it->first, "You have been kicked.\n", 22, 0);
            close(it->first);
            connectedUsers.erase(it);
            logger.log("User kicked: " + username);
            emit newMessage(QString::fromStdString(username + " has been kicked."));
            emit userListUpdated();
            break;
        }
    }
}

void TCPServer::banUser(const std::string& username) {
    bannedUsers.push_back(username);
    for (auto it = connectedUsers.begin(); it != connectedUsers.end(); ++it) {
        if (it->second.username == username) {
            send(it->first, "You have been banned.\n", 22, 0);
            close(it->first);
            connectedUsers.erase(it);
            logger.log("User banned: " + username);
            emit newMessage(QString::fromStdString(username + " has been banned."));
            emit userListUpdated();
            break;
        }
    }
    saveUsersToFile();
}

std::vector<ConnectedUser> TCPServer::getConnectedUsers() const {
    std::vector<ConnectedUser> users;
    for (const auto& client : connectedUsers) {
        users.push_back(client.second);
    }
    return users;
}

void TCPServer::process() {
}

void TCPServer::loadUsersFromFile() {
}

void TCPServer::saveUsersToFile() {
}
