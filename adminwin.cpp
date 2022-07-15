#include "adminwin.h"
#include "ui_adminwin.h"

AdminWin::AdminWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWin)
{
    ui->setupUi(this);
}

AdminWin::~AdminWin()
{
    delete ui;
}
