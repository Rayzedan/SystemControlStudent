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
    SWindow = new StudentWindow();
    connect(SWindow, &StudentWindow::firstWindow, this, &AuthorizationWindow::show);
    AWindow = new AdminWindow();
    connect(AWindow, &AdminWindow::firstWindow, this, &AuthorizationWindow::show);
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
            this->close();
            AWindow->show();
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
            this->close();
            SWindow->show();
        }
        else
        {
            QMessageBox::critical(this, "Авторизация", "Вы ввели неправильные данные");
        }
    }
}




