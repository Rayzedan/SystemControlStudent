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
    AWindow = new AdminWindow();
    //Связываем окно авторизации и окно студента
    connect(SWindow, &StudentWindow::firstWindow, this, &AuthorizationWindow::show);
    //Связываем окно авторизации и окно администратора
    connect(AWindow, &AdminWindow::firstWindow, this, &AuthorizationWindow::show);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}


void AuthorizationWindow::on_pushButton_clicked() //Кнопка авторизации
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString Mode = ui->choiseMenu->currentText();
    if (Mode == "Администратор") //В зависимости от режима поставленного в ComboBox открываем нужное окно
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




