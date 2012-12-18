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
    connect(client,SIGNAL(updateClients(QString)),this,SLOT(updateClient(QString)));
    connect(client,SIGNAL(connected()),this,SLOT(slotConnect()));
    connect(client,SIGNAL(disconnected()),this,SLOT(slotDisconnect()));
    connect(SetServer,SIGNAL(clicked()),this,SLOT(setserver()));
    connect(send,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(message,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ch_name,SIGNAL(triggered()),this,SLOT(changename()));
    connect(logout,SIGNAL(triggered()),client,SLOT(disconnectFromHostImplementation()));
    connect(login,SIGNAL(triggered()),this,SLOT(setserver()));
}
void chat::slotConnect(){
    text->clear();
    login->setEnabled(false);
    logout->setEnabled(true);
    SetServer->setEnabled(false);
    Addr->setEnabled(false);
    Port->setEnabled(false);
    message->setEnabled(true);
    send->setEnabled(true);
}
void chat::slotDisconnect(){
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
    return 0;
}

void chat::sendMessage(){
    if (message->text().isEmpty()){
        return ;
    }else{
        QString msg=MyNickname+":"+message->text();
        if (strlen(msg.toUtf8())<1024){
            client->sendMessage(msg);
        }
        message->clear();
    }
    return ;
}

void chat::updateClient(QString msg){
    QString Nickname=msg;
    for (int i=0;i<Nickname.length();i++){
        if (msg[i]==':'){
            Nickname.resize(i);
            msg=msg.right(msg.length()-i-1);
            break;
        }
    }
    appendMessage(Nickname,msg);
}
void chat::changename(){
    chname * dlg;
    dlg=new chname(this);
    dlg->returnname= & MyNickname;
    dlg->exec();
}

chat::~chat()
{
}
