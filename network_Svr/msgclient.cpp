#include "msgclient.h"
#include <windows.h>
#include <string>
msgclient::msgclient(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    blocksize=0;
}
void msgclient::dataReceived(){
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_8);
    if (blocksize==0){
        if (bytesAvailable()<sizeof(quint16)) return;
        in>>blocksize;
    }
    if (bytesAvailable()<blocksize) return;
    QString message;
    in>>message;
    /*char *buf = new char[blocksize+10];
    in.readRawData(buf,blocksize);
    QByteArray arr(buf,blocksize);
    delete buf;*/
    blocksize=0;
    msgEncode msg(message);
    emit updateClients(msg);
}
