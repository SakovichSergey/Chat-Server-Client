#ifndef WIDGET_H
#define WIDGET_H
#include <QTime>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QTcpSocket>
#include <QTcpServer>
#include <QShortcut>
#include "client.h"
#include "message.h"

class Widget : public QWidget
{
    Q_OBJECT    //Макрос
public:
    QHBoxLayout *form, *twoButton; //Слои: общий и для двух кнопок(Отправить и настройки/выход)
    QVBoxLayout *chatLayout, *settings, *userListLayout;//Слой чат, настроек и список пользователей
    QLabel *lbl1,*lbl2,*lbl3,*lbl4,*lbl5,*lbl6; //Метки пассивные
    QTextBrowser *ctWND; //Текстовый броузер для отображения сообщений
    QLineEdit *port,*name,*mess,*encryptKey;    //Текстовые поля для ввода данных(адрес и порт сервера, ник, текст сообщения, ключ/и шифрования)
    QPushButton *send, *set, *start; //Кнопки(Отправить, настройки/выход, старт(присоединится к серверу))
    QCheckBox *useShifro; //Чекбокс включить шифрование
    QGroupBox *sttngs,*usrlst; //Группировки настроек и списка пользователей
    QListWidget *userListBox; //Список пользователей
    QShortcut *keyEnter;
    QString username; //Ник
    QString recpMess; //Получатель сообшени, по умолчанию ALL
    QString adress; //Адресс
    int nport; //Номер порта
    bool privMess; //Флаг приватного сообщения
    client *chatClient; //Клиент
    Message *outMessage; // Сообщение
    Widget(QWidget *parent = nullptr); //Конструктор
    ~Widget();  //Деструктор
    void set_UserInterface(); //Метод настройки формы

public slots:
    void click_Start();     //Слот нажатия кнопки старт
    void click_Set();       //Слот нажатия кнопки настройки
    void use_Encryption();  //Слот включения шифрования
    void send_Message();    //Слот отправки сообщения
    void change_User();         //Слот выбора пользователя для персонального сообщения
    void change_PrivateUser();  //Слот выбора пользователя для приватного сообщения
    void accept_Message();  //Слот приема сообщения
    void add_NewUser(QString userName); //Слот добавления нового пользователя
    void set_UserList(QStringList userList); //Слот получение списка пользователей
};
#endif // WIDGET_H
