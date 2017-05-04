#include "regedit.h"
#include "ui_regedit.h"

regedit::regedit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regedit)
{
    ui->setupUi(this);
}

regedit::~regedit()
{
    delete ui;
}
