#ifndef WIDGET_H
#define WIDGET_H
#include "regeditdialog.h"
#include "repasswddialog.h"
#include <QWidget>
#include <QLabel>
#include <QNetworkReply>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_btn_login_clicked();

    void lab_regedit_clicked();

    void lab_reset_clicked();

    void requestFinished(QNetworkReply *reply);

    void on_checkBox_clicked();

private:
    Ui::Widget *ui;
    regeditDialog *rgDialog;
    repasswdDialog *reDialog;
};

#endif // WIDGET_H
