#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "ui_tcpserver.h"
#include "megserver.h"

class Tcpserver : public QDialog, private Ui::Tcpserver
{
    Q_OBJECT
    
public:
    explicit Tcpserver(QWidget *parent = 0);
public slots:
    void start_listen();
    void NewMessage(QString);
private:
    megserver * server;
};

#endif // TCPSERVER_H
