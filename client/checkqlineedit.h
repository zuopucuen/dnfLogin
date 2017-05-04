#ifndef CHECKQLINEEDITOR_H
#define CHECKQLINEEDITOR_H
#include <QLineEdit>
class CheckQLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CheckQLineEdit(QWidget *parent = 0);
    ~CheckQLineEdit();

    bool isValidity();

private slots:

private:

};

#endif // CHECKQLINEEDITOR_H
