#include "adminwindow.h"
#include "ui_adminwindow.h"


AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_toolButton_clicked()
{
    //QString QFileDialog::getOpenFileName();
}

