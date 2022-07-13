#include "authorizationwindow.h"
#include "adminwindow.h"
#include "./ui_authorizationwindow.h"
#include <QMessageBox>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    AdmWindow = new AdminWindow();
    //Связываем окно авторизации и окно администратора
    connect(AdmWindow, &AdminWindow::backToAuth, this, &AuthorizationWindow::show);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}


void AuthorizationWindow::on_pushButton_2_clicked() //Кнопка авторизации
{
    QString login = ui->login->text();
    QString password = ui->password->text();
        if(login == "Test" && password =="123")
        {
            QMessageBox::information(this,"Авторизация","Успешный вход");
            AdmWindow->show();
            this->close();

        }
        else
        {
            QMessageBox::critical(this, "Авторизация", "Вы ввели неправильные данные");
        }
}

void AuthorizationWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}

