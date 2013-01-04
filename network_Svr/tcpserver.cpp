#include "tcpserver.h"
#include <set>

Tcpserver::Tcpserver(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    server = new megserver(parent);
    setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint);
    connect(this->pb_start,SIGNAL(clicked()),this,SLOT(start_listen()));
    connect(server,SIGNAL(GetMessage(msgEncode)),this,SLOT(NewMessage(msgEncode)));
}

void Tcpserver::start_listen(){
    server->close();
    if (server->listen(QHostAddress::Any,port->text().toInt())){
        pb_start->setEnabled(false);
        //listen�ɹ�
    }else{
        //listenʧ��
    }
}
void Tcpserver::NewMessage(msgEncode msg){
    text->append(msg.getName()+":"+msg.getmsg());
}
