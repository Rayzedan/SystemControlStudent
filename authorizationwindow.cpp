#include "authorizationwindow.h"
#include "adminwindow.h"
#include "./ui_authorizationwindow.h"
#include <QMessageBox>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    // Скрываем пароль, который вводит администратор
    ui->password->setEchoMode(QLineEdit::Password);

    // Выделяем память для окна администратора
    AdmWindow = new AdminWindow();

    // Связываем окно авторизации и окно администратора
    connect(AdmWindow, &AdminWindow::backToAuth, this, &AuthorizationWindow::show);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

// Кнопка авторизации
void AuthorizationWindow::on_pushButton_2_clicked()
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

// Кнопка возврата к начальному окну
void AuthorizationWindow::on_pushButton_clicked()
{
    this->destroy();
    emit firstWindow();
}

