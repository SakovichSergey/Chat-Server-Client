#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTableWidget>
#include <QDateTime>
#include <QHeaderView>
#include "server.h"

class Widget : public QWidget
{
    Q_OBJECT
    QHBoxLayout     *form;
    QVBoxLayout     *tableLayot;
    QVBoxLayout     *userListLayot;
    QTableWidget    *messageTable;
    QListWidget     *userListBox;
    QLineEdit       *messageEdit;
    QPushButton     *sendMessageButton,*exitButton;
    QLabel          *lblUserList,   *lblTableChat,  *lblMessageEdit;
    QDateTime        currentTime;
    QVector<ChatUser> *userList;
    Server *chatServer;
    void setHeaderColumnMessageTable(QStringList HeaderList);
    QTableWidgetItem* stringToMessageTableItem(QString str);
    void fillMessageTable(Message *message);
    void clickMessageButton();
    void pushExitButton();
    void doubleClickDelUser();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void createUIForm();
public slots:
    void addNewUser(QString userName);
    void delUser(QString userName);
    void acceptMessage(Message *msg);
};
#endif // WIDGET_H
