#ifndef MSGENCODE_H
#define MSGENCODE_H
#include <QString>
#include <cstdlib>
#include <QtNetwork>
class msgEncode
{
    QString Nickname;
    QString message;
public:
    msgEncode(QByteArray line);
    msgEncode(QString msg);
    msgEncode(QString name,QString msg);
    QString getName();
    QString getmsg();
    QByteArray block;
    QByteArray toStream();
};

#endif // MSGENCODE_H
