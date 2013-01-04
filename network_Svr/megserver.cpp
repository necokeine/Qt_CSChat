#include "megserver.h"
#include <cstdlib>

megserver::megserver(QObject *parent, int port):
    QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void megserver::incomingConnection(int handle){
    msgclient * nowcon= new msgclient(this);
    connect(nowcon,SIGNAL(updateClients(msgEncode)),this,SLOT(updateClient(msgEncode)));
    connect(nowcon,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    nowcon->setSocketDescriptor(handle);
    TcpSocketList.append(nowcon);
    //����һ���Ի��߳�
}

void megserver::updateClient(msgEncode msg){
    emit GetMessage(msg);
    for (int i=0;i<TcpSocketList.size();i++){
        QTcpSocket *item=TcpSocketList.at(i);
        if (item->write(msg.toStream())){
            continue;
            //���ﴦ��һ��ʧЧ������
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

void megserver::PushMessage(msgEncode msg){
    updateClient(msg);
    //����һ���߳�
}


