#include "widget.h"

Widget::~Widget()
{
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    set_UserInterface();
    connect(start, &QPushButton::clicked, this, &Widget::click_Start);
    connect(set, &QPushButton::clicked, this, &Widget::click_Set);
    connect(useShifro,&QCheckBox::clicked,this,&Widget::use_Encryption);
    connect(send, &QPushButton::clicked, this, &Widget::send_Message);
    connect(keyEnter,&QShortcut::activated, this, &Widget::send_Message);
    connect(mess,&QLineEdit::returnPressed,this, &Widget::send_Message);
    connect(userListBox,&QListWidget::clicked, this, &Widget::change_User);
    connect(userListBox,&QListWidget::doubleClicked, this, &Widget::change_PrivateUser);
    connect(useShifro,&QCheckBox::clicked, this, &Widget::create_Cryptor);
}

void Widget::click_Start()
{
    QStringList adr = port->text().split(':');
    adress = adr[0];
    nport = adr[1].toInt();
    username = name->text();
    setWindowTitle("Chat:"+username);
    chatClient =  new client(adress,nport);
    if(chatClient->clientSock->isValid())
       {
        chatClient->clientSock->write(QByteArray::fromStdString(username.toStdString()));
        ctWND ->setText("Chat connect");
        sttngs->hide();
        usrlst->show();
        set->setText("Settings");
        }
    else
    {
        ctWND ->setText("Server is out");
    }
   connect(chatClient->nMessage, &Message::accept_MessageSignal,this,&Widget::accept_Message);
   connect(chatClient->nMessage, &Message::add_user, this, &Widget::add_NewUser);
   connect(chatClient->nMessage, &Message::add_UserList, this, &Widget::set_UserList);
}
void Widget::click_Set()
{
    if(sttngs->isHidden()&&usrlst->isVisible())
    {
        sttngs->show();
        usrlst->hide();
        set->setText("Exit");
        QString byeMsg = "COMMAND*GOODBYE*";
        byeMsg += username;
        chatClient->clientSock->write(QByteArray::fromStdString(byeMsg.toStdString()));
        chatClient->clientSock->disconnectFromHost();
    }
    else if(sttngs->isVisible())
    {
        exit(EXIT_FAILURE);
    }
}
void Widget::use_Encryption()
{
    if(useShifro->isChecked())
    {
    lbl6->show();
    encryptKey->show();
    }
    else
    {
        lbl6->hide();
        encryptKey->hide();
    }
}
void Widget::set_UserInterface()
{
    setWindowTitle("ChatClient");
    form = new QHBoxLayout(); //Главная форма
    twoButton = new QHBoxLayout();//Слой с кнопками отправить и настройка
    chatLayout = new QVBoxLayout(); //Слой окна чата
    settings = new QVBoxLayout();//Слой настроек
    userListLayout= new QVBoxLayout(); //Слой списка пользователей
    lbl1= new QLabel();
    lbl1->setText("Port");
    lbl2= new QLabel();
    lbl2->setText("Name");
    lbl3= new QLabel();
    lbl3->setText("Chat");
    lbl4= new QLabel();
    lbl4->setText("Message");
    lbl5= new QLabel();
    ctWND = new QTextBrowser();
    port = new QLineEdit();
    name = new QLineEdit();
    mess = new QLineEdit();
    send = new QPushButton();
    send->setText("Send");
    set = new QPushButton();
    set->setText("Settings");
    start = new QPushButton();
    start ->setText("Start");
    useShifro = new QCheckBox();
    sttngs= new QGroupBox();
    chatLayout->addWidget(lbl3);
    chatLayout->addWidget(ctWND);
    chatLayout->addWidget(lbl4);
    chatLayout->addWidget(mess);
    chatLayout->addLayout(twoButton);
    twoButton->addWidget(send);
    twoButton->addWidget(set);
    form->addLayout(chatLayout);
    settings->addWidget(lbl1);
    settings->addWidget(port);
    settings->addWidget(lbl2);
    settings->addWidget(name);
    settings->addWidget(lbl5);
    settings->addWidget(start);
    sttngs->setLayout(settings);
    useShifro = new QCheckBox();
    settings->addWidget(useShifro);
    useShifro->setText("Encryption ON");
    lbl6 = new QLabel();
    lbl6->setText("Encryption key");
    settings->addWidget(lbl6);
    encryptKey = new QLineEdit();
    settings->addWidget(encryptKey);
    lbl6->hide();
    encryptKey->hide();
    sttngs->setTitle("Settings");
    sttngs->setFixedWidth(200);
    form->addWidget(sttngs);
    userListBox = new QListWidget();
    usrlst = new QGroupBox();
    usrlst->setFixedWidth(200);
    userListLayout ->addWidget(userListBox);
    usrlst->setTitle("Chat clients");
    usrlst->setLayout(userListLayout);
    form->addWidget( usrlst);
    usrlst->hide();
    setLayout(form);
    lbl1 ->setText("IP:Port");
    port ->setText("127.0.0.1:3232");
    name->setText("Upiter");
    recpMess = "ALL";
    privMess = false;
    keyEnter = new QShortcut(this);
    keyEnter->setKey(Qt::Key_Enter);
}


void Widget::send_Message()
{
    outMessage = new Message();
    outMessage->messageSender = username;
    outMessage->messageRecipient =  recpMess;
    outMessage->messageTime = QTime::currentTime().toString();
    outMessage->messageText = mess->text();
    if(outMessage->messageRecipient == "ALL")
    outMessage->messageAttributes ="Public";
    else if(outMessage->messageRecipient != "ALL")
    outMessage->messageAttributes ="Personal";
    if(outMessage->messageAttributes =="Personal" && privMess == true)
        outMessage->messageAttributes ="Private";
    if(useShifro->isChecked()==true)
       {
         outMessage->messageAttributes ="Protected";
         outMessage->messageText = cryptDecryptor->messToCodeTwo(mess->text());//message_ToCode(mess->text());
       }
       else
       {
       outMessage->messageText = mess->text();
       }
    outMessage->create_Message();
    chatClient->clientSock->write(QByteArray::fromStdString(outMessage->message.toStdString()));
}

void Widget::change_User()
{
    int i = userListBox->currentRow();
    QString str = userListBox->item(i)->text();
    if(recpMess == str)
    {
        recpMess="ALL";
        userListBox->clearSelection();
    }
    else if(recpMess != str)
    {
        recpMess=str;
    }
}

void Widget::change_PrivateUser()
{
    int i = userListBox->currentRow();
    QString str = userListBox->item(i)->text();
    if(privMess==true)
    {
        str.resize(str.size()-1);
        userListBox->item(i)->setText(str);
        userListBox->clearSelection();
        recpMess="ALL";
        privMess = false;
    }
    else if(privMess == false)
    {

        str += "*";
        userListBox->item(i)->setText(str);
        privMess = true;
    }
}

void Widget::accept_Message()
{
   QString mess;
      if(useShifro->isChecked()==true && chatClient->nMessage->messageAttributes == "Protected")
      {
          chatClient->nMessage->messageText = cryptDecryptor->code_ToMessage(chatClient->nMessage->messageText);
          mess =chatClient->nMessage->messageSender+" protected:"+chatClient->nMessage->messageText;
      }
   if(chatClient->nMessage->messageAttributes == "Public")
   mess=chatClient->nMessage->messageSender +":"+chatClient->nMessage->messageText;
   else if(chatClient->nMessage->messageAttributes == "Personal")
   mess=chatClient->nMessage->messageSender+"->"+chatClient->nMessage->messageRecipient+":"+chatClient->nMessage->messageText;
   else if(chatClient->nMessage->messageAttributes == "Private")
   mess=chatClient->nMessage->messageSender+" private message to "+chatClient->nMessage->messageRecipient+":"+chatClient->nMessage->messageText;
   ctWND->append(mess);
}

void Widget::add_NewUser(QString userName)
{
   userListBox->addItem(userName);
}

void Widget::set_UserList(QStringList userList)
{
    userListBox->clear();
    for(int i = 0; i<userList.length();i++)
    if(userList[i]!="")
    userListBox->addItem(userList[i]);
}
void Widget::create_Cryptor()
{
    if(useShifro->isChecked()==true)
    {
        ctWND->append("Inputs encryption key.");
        cryptDecryptor = new Shifro(encryptKey->text());
    }
    else if(useShifro->isChecked()==false)
    {
        ctWND->append("Encryption is out");
        cryptDecryptor->~Shifro();
    }

}

