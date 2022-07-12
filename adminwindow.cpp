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
    questionedit form;
    form.setModal(true);
    form.exec();
}


void AdminWindow::on_toolButton_3_clicked()
{
    departedit form;
    form.setModal(true);
    form.exec();
}


void AdminWindow::on_toolButton_4_clicked()
{
    courseedit form;
    form.setModal(true);
    form.exec();
}


void AdminWindow::on_ButDeppart_clicked()
{
    topicedit form;
    form.setModal(true);
    form.exec();
}

