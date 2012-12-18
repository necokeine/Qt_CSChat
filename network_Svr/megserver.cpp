#include "megserver.h"
#include <cstdlib>

megserver::megserver(QObject *parent, int port):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void megserver::incomingConnection(int handle){
    msgclient * nowcon= new msgclient(this);
    connect(nowcon,SIGNAL(updateClients(QString)),this,SLOT(updateClient(QString)));
    connect(nowcon,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    nowcon->setSocketDescriptor(handle);
    TcpSocketList.append(nowcon);
    //启动一个对话线程
}

void megserver::updateClient(QString msg){
    emit GetMessage(msg);
    for (int i=0;i<TcpSocketList.size();i++){
        QTcpSocket *item=TcpSocketList.at(i);
        if (item->write(msg.toUtf8())){
            continue;
            //这里处理一下失效的连接
        }
    }
}

void megserver::slotDisconnected(int handle){
    for (int i=0;i<TcpSocketList.size();i++){
        QTcpSocket *item=TcpSocketList.at(i);
        if (item->socketDescriptor()==handle){
            TcpSocketList.removeAt(i);
            return;
        }
    }
    return;
}
void megserver::PushMessage(QString msg){
    updateClient(msg);
    //启动一个线程
}


