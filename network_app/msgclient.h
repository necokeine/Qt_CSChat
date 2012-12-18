#ifndef MSGCLIENT_H
#define MSGCLIENT_H

#include <QObject>
#include <QString>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpSocket>
class msgclient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit msgclient(QObject *parent = 0);
    void sendMessage(QString msg);

signals:
    void updateClients(QString);
    void disconnected(int);
protected slots:
    void dataReceived();
    
};

#endif // MSGCLIENT_H
