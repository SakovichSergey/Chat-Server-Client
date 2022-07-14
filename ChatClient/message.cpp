#include "message.h"

Message::Message(QObject *parent):QObject(parent)
{

}
void Message::create_Message()
{
    message = messageSender + "*" + messageRecipient + "*" + messageTime + "*" + messageText + "*" + messageAttributes;
}
QString Message::get_Message()
{
    /*
    Набор проверок ввода всех данных формы
    */
    create_Message();
    return message;
}

void Message::accept_Message(QString str)
{
    QStringList mes = str.split('*');
    if(mes.length() == 5)
    {
    messageSender = mes[0];
    messageRecipient = mes[1];
    messageTime = mes[2];
    messageText = mes[3];
    messageAttributes  = mes[4];
    emit accept_MessageSignal();
    }
    else if(mes.length() == 3)
    {
        if(mes[0] =="COMMAND")
        {    if(mes[1]=="NEWUSERNAME")
            {
                emit add_user(mes[2]);
            }
            else if(mes[1]=="USERLIST")
            {
                QStringList userlist = mes[2].split(":");
                emit add_UserList(userlist);
            }
        }
    }
}
