#include "widget.h"
#include "ui_widget.h"
#include "aes_cbc.h"
#include "httpaesrequest.h"
#include "util.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QProcess>
#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QByteArray dnfInfoData;
    QList<QByteArray> dnfInfoList;
    QFile file("./dnf.exe");
    AES_CBC aes;

    this->setTabOrder(ui->text_user, ui->text_passwd);
    this->setTabOrder(ui->text_passwd, ui->btn_login);
    ui->setupUi(this);

    if (!file.exists()){
        QMessageBox::warning(this,tr("Warning"), tr("没有找到你DNF.exe，请将登录器放置到游戏安装目录！"), QMessageBox::Ok);
        exit(1);
    };

    if(!changeHostFile()){
        QMessageBox::warning(this,tr("Warning"), tr("hosts修改失败，请手动配置：\n\r103.37.162.118 start.dnf.tw"), QMessageBox::Ok);
    }

    QFile saveFile("./dnfinfo.dat");
    QTextStream textRead(&saveFile);

    if(saveFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        dnfInfoData = aes.decrypt(textRead.readAll().toLocal8Bit());
        dnfInfoList = dnfInfoData.split('|');
        if(dnfInfoList.size()>1 && dnfInfoList.at(0).size()>6 && dnfInfoList.at(1).size()>6){
            ui->text_user->setText(dnfInfoList[0]);
            ui->text_passwd->setText(dnfInfoList[1]);
            ui->checkBox->setChecked(true);
        }
    }

    connect(ui->lab_regedit, SIGNAL(clicked()), this, SLOT(lab_regedit_clicked()));
    connect(ui->lab_reset, SIGNAL(clicked()), this, SLOT(lab_reset_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_login_clicked()
{
    QString macAddr;
    QByteArray postData;
    QByteArray dnfInfoData;
    AES_CBC aes;
    QFile saveFile("./dnfinfo.dat");

    if(ui->text_passwd->text().isEmpty()
            || ui->text_user->text().isEmpty()){
        QMessageBox::warning(this,tr("Error"),tr("请输入用户名和密码"),QMessageBox::Ok);
        return;
    }

    if (processExistsByName(TEXT("DNF.exe"))) {
        QMessageBox::warning(this,tr("Warning"), tr("DNF运行中，请关闭后重试!"), QMessageBox::Ok);
        return;
    }

    if(!ui->text_passwd->isValidity() && !ui->text_passwd->isValidity()) {
        QMessageBox::warning(this,tr("Warning"), tr("用户名或密码不合法，只能包含a-z、A-Z、0-9"), QMessageBox::Ok);
        return;
    }

    if(ui->checkBox->isChecked()) {
        dnfInfoData.append(ui->text_user->text());
        dnfInfoData.append("|");
        dnfInfoData.append(ui->text_passwd->text());

        dnfInfoData = aes.encrypt(dnfInfoData);

        if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
             QMessageBox::warning(this,tr("waring"),tr("无法保存用户名和密码！"),QMessageBox::Yes);
        }else{
            QTextStream in(&saveFile);
            in << dnfInfoData;
            saveFile.close();
        }
    }else{
        saveFile.remove();
    }

    macAddr = getMacAddr();

    postData.append("login|");
    postData.append(ui->text_user->text());
    postData.append("|");
    postData.append(QCryptographicHash::hash (
                        ui->text_passwd->text().toAscii(),
                        QCryptographicHash::Md5).toHex());
    postData.append("|");
    postData.append(macAddr);

    HttpAesRequest *loginRequest = new HttpAesRequest();

    connect(loginRequest,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(requestFinished(QNetworkReply*)));

    loginRequest->sendPOST(postData);
}


void Widget::requestFinished(QNetworkReply *reply)
{
    QStringList dnfArgs;
    QProcess process;
    AES_CBC aes;
    QByteArray response;

    response = aes.decrypt(reply->readAll());
    reply->deleteLater();

    qDebug()<< response;
    dnfArgs.append(response);


    if(!process.startDetached("dnf.exe", dnfArgs)) {
        QMessageBox::warning(this,tr("Error"),tr("启动失败，请关闭后重试！"),QMessageBox::Ok);
        return;
    }

    setWindowState(Qt::WindowMinimized);
}

void Widget::lab_regedit_clicked()
{
    rgDialog = new regeditDialog();
    rgDialog->show();
}

void Widget::lab_reset_clicked()
{
    reDialog = new repasswdDialog();
    reDialog->show();
}

void Widget::on_checkBox_clicked()
{

    ui->checkBox->setChecked(ui->checkBox->isChecked());
}
