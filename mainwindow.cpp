#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationwindow.h"
#include "studentwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.openDataBase();

    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    qDebug() << "exit";
    delete ui;
}

// Кнопка выбора режим для пользователя
void MainWindow::on_pushButton_clicked()
{
    // Проверяем какая из кнопок для выбора пользователя нажата
    if (ui->radioButton->isChecked()) {

        AWindow = new AuthorizationWindow();

        // Связываем начальное окно и окно авторизации
        connect(AWindow, &AuthorizationWindow::firstWindow, this, &MainWindow::show);
        AWindow->show();
        this->close();
    }

    if (ui->radioButton_2->isChecked()) {

        SWindow = new StudentWindow();

        // Связываем начальное окно и окно формы ввода данных студентом
        connect(SWindow, &StudentWindow::firstWindow, this, &MainWindow::show);
        SWindow->show();
        this->close();
    }
}
