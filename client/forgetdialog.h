#ifndef FORGETDIALOG_H
#define FORGETDIALOG_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class forgetDialog;
}

class forgetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit forgetDialog(QWidget *parent = 0);
    ~forgetDialog();

private slots:
    void on_pushButton_clicked();
    void requestFinished(QNetworkReply *reply);

private:
    Ui::forgetDialog *ui;
};

#endif // FORGETDIALOG_H
