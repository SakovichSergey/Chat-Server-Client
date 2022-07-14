#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include "message.h"


class ChatUser
{
    friend class Widget;
    public:
    QString userNickname;
    QTcpSocket *socket;
    ChatUser(QString userNickname, QTcpSocket *socket);
};

class Server : public QObject
{
    Q_OBJECT
    QTcpServer *server;

public:
    QString adress;
    int port;
    Server(int portNumber,QObject *parent = 0);
    QTcpSocket *socketServer;
    QVector<ChatUser> *userList;
    Message *msg;
    QString message;
    void socketCreate(QString adress, int portNumber);
    void sendUserList();
    void sendNewPublicMessage(QString message);
    void sendNewPrivateMessage(QString authorName,QString reciperName,QString message);
    void removeUser(QString userName);
    int findUser(QString userName);
public slots:
    void acceptConnection();
    void userConnection();
    void messageRead();
signals:
    void newUser(QString userName);

};

#endif // SERVER_H
