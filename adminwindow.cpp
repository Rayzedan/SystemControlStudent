#include "adminwindow.h"
#include "ui_adminwindow.h"


AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    QCommonStyle style;
    ui->setupUi(this);
    ui->pushButton_4->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_toolButton_clicked()
{
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


void AdminWindow::on_pushButton_4_clicked()
{
    this->close();
    emit firstWindow();
}

