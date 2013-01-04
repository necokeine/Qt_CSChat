#include "msgencode.h"

msgEncode::msgEncode(QByteArray msg)
{
    QDataStream in(&msg, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_8);
    in>>Nickname;
    for (int i=0;i<Nickname.length();i++){
        if (Nickname[i]==':'){
            message=Nickname.right(Nickname.length()-i-1);
            Nickname.resize(i);
            break;
        }
    }
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out<<quint16(0);
    out<<Nickname+":"+message;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
}
msgEncode::msgEncode(QString msg){
    Nickname=msg;
    for (int i=0;i<Nickname.length();i++){
        if (Nickname[i]==':'){
            message=Nickname.right(Nickname.length()-i-1);
            Nickname.resize(i);
            break;
        }
    }
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out<<quint16(0);
    out<<Nickname+":"+message;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
}

msgEncode::msgEncode(QString name, QString msg){
    Nickname=name;
    message=msg;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out<<quint16(0);
    out<<Nickname+":"+message;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
}
QString msgEncode::getmsg(){
    return message;
}

QString msgEncode::getName(){
    return Nickname;
}

QByteArray msgEncode::toStream(){
    return block;
}
