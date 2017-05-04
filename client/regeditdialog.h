#ifndef REGEDITDIALOG_H
#define REGEDITDIALOG_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
    class regeditDialog;
}

class regeditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit regeditDialog(QWidget *parent = 0);
    ~regeditDialog();

private slots:
    void on_pushButton_clicked();

    void requestFinished(QNetworkReply *reply);

private:
    Ui::regeditDialog *ui;
};

#endif // REGEDITDIALOG_H
