#include "msgclient.h"
#include <windows.h>

msgclient::msgclient(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void msgclient::dataReceived(){
    while (bytesAvailable()>0){
        char buf[1024];
        int length=bytesAvailable();
        //int length=min(bytesAvailable(),1024);
        read(buf,length);
        QString msg;
        msg=QString::fromUtf8(buf,length);
        emit updateClients(msg);
    }
}
