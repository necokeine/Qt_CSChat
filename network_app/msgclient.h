#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include "msgencode.h"
#include <QObject>
#include <QString>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpSocket>
class msgclient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit msgclient(QObject *parent = 0);
    void sendMessage(msgEncode msg);
signals:
    void updateClients(msgEncode msg);
    void disconnected(int);
protected slots:
    void dataReceived();
private:
    quint16 blocksize;
    
};

#endif // MSGCLIENT_H
