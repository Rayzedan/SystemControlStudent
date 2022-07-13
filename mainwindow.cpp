#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationwindow.h"
#include "studentwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AWindow = new AuthorizationWindow();
    SWindow = new StudentWindow();
    //Связываем окно авторизации и окно студента
    connect(SWindow, &StudentWindow::firstWindow, this, &MainWindow::show);
    //Связываем окно авторизации и окно администратора
    connect(AWindow, &AuthorizationWindow::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        this->close();
        AWindow->show();
    }
    if (ui->radioButton_2->isChecked())
    {
        this->close();
        SWindow->show();
    }
}

