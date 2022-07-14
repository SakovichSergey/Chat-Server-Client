#include "widget.h"
#include "server.h"

QTableWidgetItem* Widget::stringToMessageTableItem(QString str)
{   /*Метод преобразованеи строки в данные ячейки в таблице*/
    QTableWidgetItem* retItem = new QTableWidgetItem();
    retItem->setText(str);
    return retItem;
}

void Widget::fillMessageTable(Message *message)
{
    /*Метод заполнения строки таблици*/
     int rowIter = messageTable->rowCount()-1;
     messageTable->setItem(rowIter,0, stringToMessageTableItem(message->messageSender));
     messageTable->setItem(rowIter,1, stringToMessageTableItem(message->messageRecipient));
     messageTable->setItem(rowIter,2, stringToMessageTableItem(message->messageTime));
     messageTable->setItem(rowIter,3, stringToMessageTableItem(message->messageAttributes));
     messageTable->setItem(rowIter,4, stringToMessageTableItem(message->messageText));
}

void Widget::clickMessageButton()
{
    Message outMessage;
    outMessage.messageSender = "Server";
    outMessage.messageRecipient ="ALL";
    if(userListBox->currentRow()!=-1)
    {
        outMessage.messageRecipient = userListBox->item(userListBox->currentRow())->text();
    }
    outMessage.messageTime = QTime::currentTime().toString();
    outMessage.messageText = messageEdit->text();
    if(outMessage.messageRecipient == "ALL")
    outMessage.messageAttributes ="Public";
    else if(outMessage.messageRecipient != "ALL")
    outMessage.messageAttributes ="Personal";
    this->acceptMessage(&outMessage);
    if(userListBox->currentRow()!=-1)
    {
    userListBox->clearSelection();
    outMessage.messageRecipient ="ALL";
    userListBox->setCurrentRow(-1);
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    createUIForm();
    chatServer= new Server(3232);
    userList = new QVector<ChatUser>;
    connect(sendMessageButton, &QPushButton::clicked, this, &Widget::clickMessageButton);
    connect(chatServer,&Server::newUser, this, &Widget::addNewUser);
    connect(chatServer->msg,&Message::newMessage, this, &Widget::acceptMessage);
    connect(chatServer->msg,&Message::del_User, this, &Widget::delUser);

}

Widget::~Widget()
{
}

void Widget::createUIForm()
{
    form = new QHBoxLayout(); //Создание слоя
    tableLayot = new QVBoxLayout(); //
    lblTableChat= new QLabel();
    lblTableChat->setText("Сообщения");
    tableLayot->addWidget(lblTableChat);
    messageTable = new QTableWidget(0,5,this); //Создание таблицы
    tableLayot->addWidget(messageTable);//Добавление таблици на слой
    messageTable->setHorizontalHeaderLabels(QStringList() << "Sender"<<"Recipiter"<<"Time"<<"Attribute"<<"Message"); //Установка названий колонок
    messageTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Установка свойства автоматического изменения
    //ширины колонок по содержимому
    messageTable->setFixedSize(600,600);
    lblMessageEdit= new QLabel();
    lblMessageEdit->setText("Текст сообщения");
    tableLayot->addWidget(lblMessageEdit);
    messageEdit = new QLineEdit();
    messageEdit ->setFixedSize(600,30);
    tableLayot->addWidget(messageEdit);
    form->addLayout(tableLayot);
    userListLayot = new QVBoxLayout();
    lblUserList = new QLabel();
    lblUserList->setText("Список пользователей");
    userListLayot->addWidget(lblUserList);
    userListBox = new QListWidget();
    userListBox->setFixedSize(200,600);
    userListLayot->addWidget(userListBox);
    sendMessageButton = new QPushButton();
    sendMessageButton->setText("Отправить");
    userListLayot->addWidget(sendMessageButton);
    form->addLayout( userListLayot);
    setLayout(form);

}
void Widget::addNewUser(QString userName)
{
    userListBox->addItem(userName);
    chatServer->sendUserList();
}

void Widget::delUser(QString userName)
{
    chatServer->removeUser(userName);
    userListBox->clear();
    for(ChatUser &I : *chatServer->userList)
    {
       userListBox->addItem(I.userNickname);
    }
}

void Widget::acceptMessage(Message *msg)
{
    messageTable->insertRow(messageTable->rowCount());
    fillMessageTable(msg);
    if(msg->messageAttributes=="Public" || msg->messageAttributes=="Personal")
        chatServer->sendNewPublicMessage(msg->getMessage());
    else if(msg->messageAttributes=="Private")
        chatServer->sendNewPrivateMessage(msg->messageSender,msg->messageRecipient,msg->getMessage());
}

