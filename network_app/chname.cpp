#include "chname.h"

chname::chname(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(pb_yes,SIGNAL(clicked()),this,SLOT(changename()));
    connect(pb_no,SIGNAL(clicked()),this,SLOT(reject()));
}

void chname::changename(){
    if (! name->text().isEmpty()){
        *returnname=name->text();
    }
    accept();
}

