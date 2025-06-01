#include "../include/ServerGUI.h"
#include "../include/ui_ServerGUI.h"
#include <QFile>
#include <QMessageBox>
#include <QStandardItem>

ServerGUI::ServerGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerGUI),
    server(nullptr),
    userModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    setupUI();
    loadStyles();
    
    userModel->setHorizontalHeaderLabels(QStringList() << "Username" << "IP Address" << "Status");
    ui->userTableView->setModel(userModel);
    ui->userTableView->horizontalHeader()->setStretchLastSection(true);
}

ServerGUI::~ServerGUI()
{
    if (server) {
        server->stopServer();
        serverThread->quit();
        serverThread->wait();
        delete serverThread; // Освобождаем память
        delete server;
    }
    delete ui;
}


void ServerGUI::setupUI()
{
    setWindowTitle("Chat Server Administrator (Qt5)");
    resize(800, 600);
    
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->kickButton->setEnabled(false);
    ui->banButton->setEnabled(false);
}

void ServerGUI::loadStyles()
{
    QFile file(":/styles.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

void ServerGUI::on_startButton_clicked()
{
    if (!server) {
        server = new TCPServer(8080);
        serverThread = new QThread(this);
        
        connect(server, &TCPServer::newMessage, 
                this, &ServerGUI::appendMessage);
        connect(server, &TCPServer::userListUpdated, 
                this, &ServerGUI::updateUserList);
        
        server->moveToThread(serverThread);
        connect(serverThread, &QThread::started, server, &TCPServer::start);
        
        serverThread->start();
        
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->statusLabel->setText("Server status: Running");
        logger.log("Server started on port 8080");
    }
}

void ServerGUI::on_stopButton_clicked()
{
    if (server) {
        server->stopServer();
        serverThread->quit();
        serverThread->wait();
        
        delete server;
        server = nullptr;
        
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        ui->statusLabel->setText("Server status: Stopped");
        logger.log("Server stopped");
    }
}

void ServerGUI::on_kickButton_clicked()
{
    QModelIndexList selected = ui->userTableView->selectionModel()->selectedRows();
    if (!selected.isEmpty()) {
        QString username = userModel->item(selected.first().row(), 0)->text();
        if (server) {
            server->kickUser(username.toStdString()); // Преобразование QString в std::string
            logger.log("User kicked: " + username.toStdString());
        }
    }
}

void ServerGUI::on_banButton_clicked()
{
    QModelIndexList selected = ui->userTableView->selectionModel()->selectedRows();
    if (!selected.isEmpty()) {
        QString username = userModel->item(selected.first().row(), 0)->text();
        if (server) {
            server->banUser(username.toStdString()); // Преобразование QString в std::string
            logger.log("User banned: " + username.toStdString());
        }
    }
}

void ServerGUI::updateUserList()
{
    userModel->removeRows(0, userModel->rowCount());
    
    if (server) {
        auto users = server->getConnectedUsers();
        for (const auto &user : users) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::fromStdString(user.username));
            rowItems << new QStandardItem(QString::fromStdString(user.ipAddress));
            rowItems << new QStandardItem(QString::fromStdString(user.status));
            userModel->appendRow(rowItems);
        }
    }
    
    ui->kickButton->setEnabled(userModel->rowCount() > 0);
    ui->banButton->setEnabled(userModel->rowCount() > 0);
}

void ServerGUI::appendMessage(const QString &message)
{
    ui->chatTextEdit->append(message);
    logger.log("Message: " + message.toStdString()); // Преобразование QString в std::string
}
