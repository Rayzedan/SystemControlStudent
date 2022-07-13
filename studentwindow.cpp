#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "authorizationwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
}


StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::on_pushButton_3_clicked()
{
    emit firstWindow();
    this->close();
}

