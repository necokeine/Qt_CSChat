#include "chat.h"
#include <QtGui>
#include <cstring>

chat::chat(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    MyNickname="User";
    client=new msgclient(this);
    logout->setEnabled(false);
    connect(client,SIGNAL(updateClients(msgEncode)),this,SLOT(updateClient(msgEncode)));
    connect(client,SIGNAL(connected()),this,SLOT(slotConnect()));
    connect(client,SIGNAL(disconnected()),this,SLOT(slotDisconnect()));
    connect(SetServer,SIGNAL(clicked()),this,SLOT(setserver()));
    connect(send,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(message,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ch_name,SIGNAL(triggered()),this,SLOT(changename()));
    connect(logout,SIGNAL(triggered()),this,SLOT(disconnect()));
    connect(login,SIGNAL(triggered()),this,SLOT(setserver()));
}
void chat::slotConnect(){
    login->setEnabled(false);
    logout->setEnabled(true);
    SetServer->setEnabled(false);
    Addr->setEnabled(false);
    Port->setEnabled(false);
    message->setEnabled(true);
    send->setEnabled(true);
    msgEncode msg(MyNickname,MyNickname+"login!");
    client->sendMessage(msg);
}
void chat::disconnect(){
    msgEncode msg(MyNickname,MyNickname+" logout!");
    client->sendMessage(msg);
    client->close();
}

void chat::slotDisconnect(){
    QString msg="logout form server!";
    appendMessage(MyNickname,msg);
    login->setEnabled(true);
    logout->setEnabled(false);
    SetServer->setEnabled(true);
    Addr->setEnabled(true);
    Port->setEnabled(true);
    message->setEnabled(false);
    send->setEnabled(false);
}

void chat::setserver(){
    client->close();
    if (Addr->text().isEmpty() || Port->text().isEmpty()) return;
    client->connectToHost(Addr->text(),Port->text().toInt());
}

int chat::appendMessage(QString Nickname, QString message){
    if (Nickname.isEmpty() || message.isEmpty()){
        return -1;
    }
    QTextCursor cursor(text->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + Nickname + "> :");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = text->verticalScrollBar();
    bar->setValue(bar->maximum());
    this->activateWindow();
    return 0;
}

void chat::sendMessage(){
    if (message->text().isEmpty()){
        return ;
    }else{
        msgEncode msg(MyNickname,message->text());
        client->sendMessage(msg);
        message->clear();
    }
    return ;
}

void chat::updateClient(msgEncode msg){
    QString Nickname = msg.getName();
    QString message = msg.getmsg();
    appendMessage(Nickname,message);
}
void chat::changename(){
    chname * dlg;
    dlg=new chname(this);
    QString oldNickname=MyNickname;
    dlg->returnname= & MyNickname;
    dlg->exec();
    if (! login->isEnabled()){
        msgEncode msg(MyNickname,oldNickname+" change name to "+MyNickname);
        client->sendMessage(msg);
    }
}

chat::~chat()
{
    if (! login->isEnabled()){
        msgEncode msg(MyNickname,MyNickname+" logout!");
        client->sendMessage(msg);
        client->close();
    }
}

void chat::closeEvent(QCloseEvent * event){
    return QWidget::closeEvent(event);
}
