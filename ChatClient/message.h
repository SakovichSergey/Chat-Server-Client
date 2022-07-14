#ifndef MESSAGE_H
#define MESSAGE_H
#include<QObject>
#include<QString>
#include<QStringList>

class Message : public QObject
{
   Q_OBJECT    //Макрос
    public:
    QString messageSender;          //Имя отправителя (Кто?)
    QString messageRecipient;       //Имя получателя (Кому?)
    QString messageTime;            //Время (Когда?)
    QString messageText;            //Текст сообщения (Что?)
    QString messageAttributes;      //Атрибуты сообщения: сообщение публично, приватно или защищено и т.д.
    QString message;                //Сообщение передоваемое между клиентом и сервером и пересылаемое сервером адресатам
    Message(QObject *parent = 0);                          //Конструктор
    void create_Message();              //Метод формирования сообщения
    void accept_Message(QString str);   //Метод для обработки принятых сообщений
    QString get_Message();              //Свойство для получения сообщения
signals:
    void add_user(QString userName);            //Сигнал добавлен новый пользователь
    void add_UserList(QStringList userlist);    //Сигнал добавлен список пользователей
    void accept_MessageSignal();
};
#endif // MESSAGE_H

