#ifndef MESSAGE_H
#define MESSAGE_H
#include<QObject>
#include<QString>
#include<QStringList>

class Message : public QObject
{
   Q_OBJECT    //Макрос
   // protected:
    public:
    QString messageSender;          //Имя отправителя (Кто?)
    QString messageRecipient;       //Имя получателя (Кому?)
    QString messageTime;            //Время (Когда?)
    QString messageText;            //Тест сообщения (Что?)
    QString messageAttributes;      //Атрибуты сообщения: сообщение публично, приватно или защищено и т.д.
    QString message;                //Сообщение передоваемое между клиентом и сервером и пересылаемое сервером адресатам
    void createMessage();           //Метод формирования сообщения
    Message(QObject *parent=0);
    QString getMessage();              //Свойство для получения сообщения
    void acceptMesasge(QString str);
signals:
    void del_User(QString userName);
    void newMessage(Message *msg);
};
#endif // MESSAGE_H

