#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpSocket>
#include "msgencode.h"

class msgclient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit msgclient(QObject *parent = 0);
signals:
    void updateClients(msgEncode);
    void disconnected(int);
protected slots:
    void dataReceived();
private:
    quint16 blocksize;
};

#endif // MSGCLIENT_H
