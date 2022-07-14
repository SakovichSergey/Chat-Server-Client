
#include "client.h"

client::client(QString adress, int port,QObject *parent):QObject(parent)
{
    clientSock = new QTcpSocket();
    clientSock->connectToHost(adress,port);
    nMessage = new Message();
    connect(clientSock,&QTcpSocket::readyRead,this,&client::readyRead_Socket);
}

void client::readyRead_Socket()
{
    QString  str;
    str = clientSock->readAll();

    nMessage->accept_Message(str);
}


