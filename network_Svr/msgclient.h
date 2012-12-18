#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpSocket>

class msgclient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit msgclient(QObject *parent = 0);
signals:
    void updateClients(QString);
    void disconnected(int);
protected slots:
    void dataReceived();
    
};

#endif // MSGCLIENT_H
