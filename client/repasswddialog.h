#ifndef repasswdDialog_H
#define repasswdDialog_H

#include "forgetdialog.h"
#include <QDialog>
#include <QNetworkReply>

namespace Ui {
    class repasswdDialog;
}

class repasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit repasswdDialog(QWidget *parent = 0);
    ~repasswdDialog();

private slots:
    void on_btn_repasswd_clicked();
    void requestFinished(QNetworkReply *replay);
    void lab_forget_clicked();

private:
    Ui::repasswdDialog *ui;
    forgetDialog *fgDialog;
};

#endif // repasswdDialog_H
