#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "authorizationwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    testWindow = new TestForStudent();

}


StudentWindow::~StudentWindow()
{
    delete ui;
}

// Кнопка возврата к начальному окну
void StudentWindow::on_pushButton_3_clicked()
{
    this->destroy();
    emit firstWindow();
}


void StudentWindow::on_pushButton_clicked()
{
    testWindow->show();
    this->destroy();

}

