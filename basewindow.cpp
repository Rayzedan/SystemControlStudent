#include "basewindow.h"
#include "ui_basewindow.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseWindow)
{
    questForm = new questionedit();
    ui->setupUi(this);
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::on_pushButton_3_clicked()
{
    questForm->show();
}

