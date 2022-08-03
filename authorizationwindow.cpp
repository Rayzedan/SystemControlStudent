#include "authorizationwindow.h"
#include "./ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    // Скрываем пароль, который вводит администратор
    ui->password->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setDefault(1);

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
        // Если введённые данные совпадают с тем, что ввёл пользователь - открываем окно администрирования, пока что убрал авторизацию так как данные в бд незашифрованные
        if (db->checkData(ui->login->currentText(), password_user) && mode ==false) {
            QVariantList data;
            data.append(ui->login->currentText());
            data.append(password_user);
            // Выделяем память для окна администратора
            connect(this, &AuthorizationWindow::sendData,Awin,&AdminWin::takeLogin);
            emit sendData(ui->login->currentText());
            Awin->show();
            this->close();
        }
        else if (mode == true && db->encryptPassword(password_user) == adminPassword) {
            QVariantList data;
            data.append(ui->login->currentText());
            data.append(password_user);
            connect(this, &AuthorizationWindow::sendData,Awin,&AdminWin::takeLogin);
            emit sendData(ui->login->currentText());
            Awin->show();
            this->close();
        }
        else {
            QMessageBox :: warning (NULL, "Ошибка", "Неверное имя пользователя или пароль");
        }
    ui->password->clear();
}



// Кнопка возврата к начальному окну
void AuthorizationWindow::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


void AuthorizationWindow::takePoint(AdminWin *admWin)
{
    Awin = admWin;
}

void AuthorizationWindow::startMode(bool configMode)
{
    if (configMode ==false)
    {
        qDebug() << "config mode";
        mode = true;
        ui->login->addItem("DEFAULT");
    }
    else {
        // Создаём модель для отображения всех доступных логинов из бд
        model = new QSqlQueryModel();
        model->setQuery("Select Login From Users order by Login");
        ui->login->setModel(model);
    }

}
