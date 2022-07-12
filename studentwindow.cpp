#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <authorizationwindow.h>
#include <QCommonStyle>

StudentWindow::StudentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    QCommonStyle style;
    ui->setupUi(this);
    ui->pushButton_3->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
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

