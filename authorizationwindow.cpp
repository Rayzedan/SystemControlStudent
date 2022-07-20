#include "authorizationwindow.h"
#include "./ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

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
    event->accept();
}


// Кнопка авторизации
void AuthorizationWindow::on_pushButton_2_clicked()
{
    QString password_user = ui->password->text();
    // Проверяем, что вводит пользователь
        if (password_user.isEmpty()) {
            QMessageBox :: warning (this, "", "Пароль не может быть пустым!");
        }
        // Если пройдены первичные проверки, то отправляем запрос в базу данных
        else
        // Если введённые данные совпадают с тем, что ввёл пользователь - открываем окно администрирования
             if (db->checkData(ui->login->currentText(), password_user)) {
                 QVariantList data;
                 data.append(ui->login->currentText());
                 data.append(password_user);
                // Выделяем память для окна администратора
                Awin = new AdminWin(data);
                connect(Awin, &AdminWin::secondWindow, this, &AuthorizationWindow::show);
                Awin->show();
                this->close();
        }
    ui->password->clear();
}


// Кнопка возврата к начальному окну
void AuthorizationWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


