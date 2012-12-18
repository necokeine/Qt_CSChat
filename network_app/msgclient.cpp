#include "msgclient.h"
#include <windows.h>

msgclient::msgclient(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    //connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void msgclient::dataReceived(){
    while (bytesAvailable()>0){
        char buf[1024];
        int length=bytesAvailable();
        read(buf,length);
        QString msg=QString::fromUtf8(buf,length);
    }
    emit updateClients(msg);
}
void msgclient::sendMessage(QString msg){
    write(msg.toUtf8());
}
