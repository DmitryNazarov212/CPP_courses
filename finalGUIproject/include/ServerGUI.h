#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QThread> // Добавлено
#include "ServerTCP.h"
#include "Logger.h"

namespace Ui {
class ServerGUI;
}

class ServerGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerGUI(QWidget *parent = 0);
    ~ServerGUI();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_kickButton_clicked();
    void on_banButton_clicked();
    void updateUserList();
    void appendMessage(const QString &message);

private:
    Ui::ServerGUI *ui;
    TCPServer *server;
    Logger logger;
    QStandardItemModel *userModel;
    QThread *serverThread;

    void setupUI();
    void loadStyles();
};
#endif // SERVERGUI_H
