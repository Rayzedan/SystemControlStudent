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
    // Проверяем, что вводит пользователь
        if(login == "") {
            QMessageBox :: warning (this, "", "Имя пользователя не может быть пустым!");
<<<<<<< HEAD
=======
            // Костыль
            AdmWindow->show();
            this->close();
            ui->login->clear();
            ui->password->clear();
>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)
        }
        else if (password =="") {
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
    this->destroy();
    emit firstWindow();
}

