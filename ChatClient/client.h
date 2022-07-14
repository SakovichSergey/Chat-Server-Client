#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QTcpSocket>
#include "message.h"

class client : public QObject
{
    Q_OBJECT    //Макрос
public:
    QTcpSocket *clientSock; //Сокет клиента
    Message *nMessage;      //Сообщение клиента
    client(QString adress, int port, QObject *parent = 0); //Конструктор

private slots:
    void readyRead_Socket(); //Слот для обработки поступивших данных на сокет

};

#endif // CLIENT_H
