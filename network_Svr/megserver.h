#ifndef MEGSERVER_H
#define MEGSERVER_H
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QString>
#include "msgclient.h"
#include "msgencode.h"

class megserver: public QTcpServer
{
    Q_OBJECT
public:
    megserver(QObject *parent = 0, int port = 0);
    void PushMessage(msgEncode);
    QList<msgclient *> TcpSocketList;
signals:
    void updateServer(msgEncode);
    void GetMessage(msgEncode);
public slots:
    void updateClient(msgEncode);
    void slotDisconnected(int handle);
protected:
    void incomingConnection(int handle);

};

#endif // MEGSERVER_H
