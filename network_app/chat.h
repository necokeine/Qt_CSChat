#ifndef CHAT_H
#define CHAT_H
#include "chname.h"
#include <QMainWindow>
#include "ui_chat.h"
#include "msgclient.h"

class chat : public QMainWindow,private Ui::chat
{
    Q_OBJECT
    
public:
    QString MyNickname;
    explicit chat(QWidget *parent = 0);
    ~chat();
    int appendMessage(QString Nickname,QString message);
public slots:
    void sendMessage();
    void updateClient(QString msg);
    void setserver();
    void disconnect();
    void changename();
    void slotConnect();
    void slotDisconnect();
private:
    msgclient * client;
    QTextTableFormat tableFormat;
};

#endif // CHAT_H
