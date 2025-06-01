/********************************************************************************
** Form generated from reading UI file 'ServerGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERGUI_H
#define UI_SERVERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerGUI
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLabel *statusLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTableView *userTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *kickButton;
    QPushButton *banButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *chatTextEdit;

    void setupUi(QMainWindow *ServerGUI)
    {
        if (ServerGUI->objectName().isEmpty())
            ServerGUI->setObjectName(QString::fromUtf8("ServerGUI"));
        ServerGUI->resize(800, 600);
        centralwidget = new QWidget(ServerGUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout_2->addWidget(startButton);

        stopButton = new QPushButton(groupBox);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout_2->addWidget(stopButton);

        statusLabel = new QLabel(groupBox);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        verticalLayout_2->addWidget(statusLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        userTableView = new QTableView(groupBox_2);
        userTableView->setObjectName(QString::fromUtf8("userTableView"));

        verticalLayout_3->addWidget(userTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        kickButton = new QPushButton(groupBox_2);
        kickButton->setObjectName(QString::fromUtf8("kickButton"));

        horizontalLayout_2->addWidget(kickButton);

        banButton = new QPushButton(groupBox_2);
        banButton->setObjectName(QString::fromUtf8("banButton"));

        horizontalLayout_2->addWidget(banButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        chatTextEdit = new QTextEdit(groupBox_3);
        chatTextEdit->setObjectName(QString::fromUtf8("chatTextEdit"));
        chatTextEdit->setReadOnly(true);

        verticalLayout_4->addWidget(chatTextEdit);


        verticalLayout->addWidget(groupBox_3);

        ServerGUI->setCentralWidget(centralwidget);

        retranslateUi(ServerGUI);

        QMetaObject::connectSlotsByName(ServerGUI);
    } // setupUi

    void retranslateUi(QMainWindow *ServerGUI)
    {
        ServerGUI->setWindowTitle(QCoreApplication::translate("ServerGUI", "Chat Server Administrator", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ServerGUI", "Server Controls", nullptr));
        startButton->setText(QCoreApplication::translate("ServerGUI", "Start Server", nullptr));
        stopButton->setText(QCoreApplication::translate("ServerGUI", "Stop Server", nullptr));
        statusLabel->setText(QCoreApplication::translate("ServerGUI", "Server status: Stopped", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ServerGUI", "User Management", nullptr));
        kickButton->setText(QCoreApplication::translate("ServerGUI", "Kick User", nullptr));
        banButton->setText(QCoreApplication::translate("ServerGUI", "Ban User", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ServerGUI", "Chat Messages", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerGUI: public Ui_ServerGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERGUI_H
