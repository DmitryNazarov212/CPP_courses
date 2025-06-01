#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <string>
#include <map>
#include <vector>
#include <netinet/in.h> // POSIX socket headers for Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Logger.h"
#include <mutex>


struct ConnectedUser {
    std::string username;
    std::string ipAddress;
    std::string status;
    int socket;
};

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(int port, QObject *parent = nullptr);
    bool start();
    void acceptClients();
    void handleClient(int clientSocket);
    void sendToAllClients(const std::string& message);
    void stopServer();
    void kickUser(const std::string& username);
    void banUser(const std::string& username);
    std::vector<ConnectedUser> getConnectedUsers() const;

signals:
    void newMessage(QString message);
    void userListUpdated();

public slots:
    void process();

private:
    void loadUsersFromFile();
    void saveUsersToFile();
    mutable std::mutex mutex;

    int _port;
    int _serverSocket;
    std::map<std::string, std::string> users;
    std::map<int, ConnectedUser> connectedUsers;
    Logger logger;
    std::vector<std::string> bannedUsers;
    bool running;
};

#endif // TCPSERVER_H
