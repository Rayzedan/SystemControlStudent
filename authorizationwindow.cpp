#include "authorizationwindow.h"
#include "./ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    // Выделяем память для окна администратора
    Awin = new AdminWin();
    connect(Awin, &AdminWin::secondWindow, this, &AuthorizationWindow::show);

    // Скрываем пароль, который вводит администратор
    ui->password->setEchoMode(QLineEdit::Password);

    // Создаём модель для отображения всех доступных логинов из бд
    model = new QSqlQueryModel();   

    model->setQuery("Select Login From Users");

    ui->login->setModel(model);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

// Закрываем окно
void AuthorizationWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "exit from autWin";
    ui->login->clear();
    ui->password->clear();
    event->accept();
}


// Кнопка авторизации
void AuthorizationWindow::on_pushButton_2_clicked()
{
    QString password = ui->password->text();
    // Проверяем, что вводит пользователь
        if (password =="") {
            QMessageBox :: warning (this, "", "Пароль не может быть пустым!");
            this->close();
        }
        // Если пройдены первичные проверки, то отправляем запрос в базу данных
        else
        {
            QString request = QString("select Login, Password from Users");
            QSqlQuery query;
        // Если введённые данные совпадают с тем, что ввёл пользователь - открываем окно администрирования
            if (query.exec(request)) {
                this->close();
                query.finish();
                Awin->show();
            }
            else
                QMessageBox :: warning (NULL, "Ошибка", "Неверное имя пользователя или пароль");
        }
}


// Кнопка возврата к начальному окну
void AuthorizationWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


