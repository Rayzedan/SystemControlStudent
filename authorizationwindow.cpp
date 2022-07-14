#include <QSqlQueryModel>
#include "authorizationwindow.h"
#include "adminwindow.h"
#include "connection.h"
#include "./ui_authorizationwindow.h"


AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    // Инициализация соединения с базой данных
    createConnection();

    // Скрываем пароль, который вводит администратор
    ui->password->setEchoMode(QLineEdit::Password);

    // Выделяем память для окна администратора
    AdmWindow = new AdminWindow();

    model = new QSqlQueryModel();

    // Связываем окно авторизации и окно администратора
    connect(AdmWindow, &AdminWindow::backToAuth, this, &AuthorizationWindow::show);

    model->setQuery("Select Login From Users");

    ui->login->setModel(model);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
    delete AdmWindow;
    delete model;
}

// Закрываем окно
void AuthorizationWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "exit from autWin";
    event->accept();
}


// Кнопка авторизации
void AuthorizationWindow::on_pushButton_2_clicked()
{
    QString password = ui->password->text();
    // Проверяем, что вводит пользователь
        if (password =="") {
            QMessageBox :: warning (this, "", "Пароль не может быть пустым!");
        }
        // Если пройдены первичные проверки, то отправляем запрос в базу данных
        else
        {
            QString request = QString("select Login, Password from Users");
            QSqlQuery query;
        // Если введённые данные совпадают с тем, что ввёл пользователь - открываем окно администрирования
            if (query.exec(request)) {
                AdmWindow->show();
                this->close();
                ui->login->clear();
                ui->password->clear();
            }
            else
                QMessageBox :: warning (NULL, "Ошибка", "Неверное имя пользователя или пароль");
        }
}

// Кнопка возврата к начальному окну
void AuthorizationWindow::on_pushButton_clicked()
{
    ui->login->clear();
    ui->password->clear();
    this->close();
    emit firstWindow();
}

