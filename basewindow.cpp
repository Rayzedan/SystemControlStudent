#include "basewindow.h"
#include "ui_basewindow.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseWindow)
{
    changeSet = new ChangeSettings();
    questForm = new questionedit();
    ui->setupUi(this);
}

BaseWindow::~BaseWindow()
{
    delete ui;
    delete changeSet;
    delete questForm;
}

void BaseWindow::on_pushButton_3_clicked()
{
    questForm->show();
}


void BaseWindow::on_pushButton_4_clicked()
{
    changeSet->show();
}

void BaseWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit backToAdm();
}
