#include "checkqlineedit.h"
#include <QDebug>

CheckQLineEdit::CheckQLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}

CheckQLineEdit::~CheckQLineEdit()
{

}

bool CheckQLineEdit::isValidity()
{
    int i;
    int length;
    QString line_text;
    char tmp;

    line_text = this->text();
    length = line_text.size();

    if(length < 0) {
        return false;
    }

    for(i=0;i<length;i++){
        tmp = line_text.at(i).toAscii();
        if((tmp<48) || (65>tmp>57) || (97>tmp>90) || (tmp>122)){
            return false;
        }
    }

    return true;
}
