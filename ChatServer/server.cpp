#include "server.h"
#include <QDebug>
#include <QCoreApplication>

Server::Server(int portNumber,QObject *parent):QObject(parent)
{
    server = new QTcpServer();
    port = portNumber;
    server->listen(QHostAddress::Any, port);
    msg = new Message();
    connect(server, &QTcpServer::newConnection, this, &Server::acceptConnection);
    userList = new QVector<ChatUser>;
}

void Server::acceptConnection()
{
    userList->push_back(ChatUser("noname", server->nextPendingConnection()));
    connect(userList->last().socket, &QTcpSocket::readyRead, this, &Server::userConnection);
}

void Server::userConnection()
{
    QString userName;
    userName = userList->last().socket->readAll();
    userList->last().userNickname  = userName;
    emit newUser(userName);
    disconnect(userList->last().socket, &QTcpSocket::readyRead, this, &Server::userConnection);
    connect(userList->last().socket, &QTcpSocket::readyRead, this, &Server::messageRead);
}

void Server::messageRead()
{
     QByteArray array;
     QTcpSocket *sock = static_cast<QTcpSocket*>(sender());
    if(sock->bytesAvailable()>0)
    { array = sock->readAll();
     msg->acceptMesasge(array);

    }
}

void Server::sendUserList()
{
   QString command;
   command = "COMMAND";
   command += "*";
   command += "USERLIST";
   command +="*";
   for(int i =0 ; i< userList->length(); i++)
    {
       command += userList->at(i).userNickname;
       command += ":";
    }
    QByteArray ulSet = QByteArray::fromStdString(command.toStdString());
    for(int i =0 ; i< userList->length(); i++)
        userList->at(i).socket->write(ulSet);
}

void Server::sendNewPublicMessage(QString message)
{
    QByteArray ulSet = QByteArray::fromStdString(message.toStdString());
    for(int i =0 ; i< userList->length(); i++)
        userList->at(i).socket->write(ulSet);
}

void Server::sendNewPrivateMessage(QString authorName,QString reciperName, QString message)
{
    QByteArray ulSet = QByteArray::fromStdString(message.toStdString());
    userList->at(findUser(authorName)).socket->write(ulSet);
    userList->at(findUser(reciperName)).socket->write(ulSet);
}

void Server::removeUser(QString userName)
{
    userList->remove(findUser(userName));
}

int Server::findUser(QString userName)
{
    int i =0;
    while( i< userList->length())
    {
        if(userList->at(i).userNickname == userName)
        {
            break;
        }
        else
        {
            i++;
        }
    }
    return i;
}
ChatUser::ChatUser(QString userNickname, QTcpSocket *socket)
{
    this->userNickname = userNickname;
    this->socket = socket;

}
