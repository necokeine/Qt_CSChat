#ifndef CHNAME_H
#define CHNAME_H

#include "ui_chname.h"

class chname : public QDialog, private Ui::chname
{
    Q_OBJECT
    
public:
    explicit chname(QWidget *parent = 0);
    QString * returnname;
public slots:
    void changename();
};

#endif // CHNAME_H
