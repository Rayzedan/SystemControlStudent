#include "authorizationwindow.h"
#include "./ui_authorizationwindow.h"
#include "adminwindow.h"
#include "studentwindow.h"
#include <QMessageBox>

AuthorizationWindow::AuthorizationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}


void AuthorizationWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString Mode = ui->choiseMenu->currentText();
    if (Mode == "Администратор")
    {
        if(login == "Test" && password =="123")
        {
            QMessageBox::information(this,"Авторизация","Успешный вход");
            AdminWindow window;
            QMainWindow::close();
            window.setModal(true);
            window.exec();
        }
        else
        {
            QMessageBox::critical(this, "Авторизация", "Вы ввели неправильные данные");
        }
    }
    else
    {
        if(login == "Test" && password =="123")
        {
            QMessageBox::information(this,"Авторизация","Успешный вход");
            StudentWindow window;
            QMainWindow::close();
            window.setModal(true);
            window.exec();
        }
        else
        {
            QMessageBox::critical(this, "Авторизация", "Вы ввели неправильные данные");
        }
    }
}




