#include "message.h"

Message::Message(QObject *parent):QObject(parent)
{

}
void Message::createMessage()
{
    message = messageSender + "*" + messageRecipient + "*" + messageTime + "*" + messageText + "*" + messageAttributes;
}
QString Message::getMessage()
{
    /*
    Набор проверок ввода всех данных формы
    */
    createMessage();
    return message;
}

void Message::acceptMesasge(QString str)
{
    QStringList mes = str.split('*');
    if(mes.length() == 5)
  {
    messageSender = mes[0];
    messageRecipient = mes[1];
    messageTime = mes[2];
    messageText = mes[3];
    messageAttributes  = mes[4];
    emit newMessage(this);
  }
    else if(mes.length() == 3)
     if(mes[0] =="COMMAND")
       if(mes[1]=="GOODBYE")
        {
            emit del_User(mes[2]);
        }
}
