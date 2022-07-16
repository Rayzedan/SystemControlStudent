#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationwindow.h"
#include "studentwindow.h"
#include "adminwin.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // При запуске программы окно будет расположено прямо по центру
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(this);
    QPoint center = rect.center();
    int x = center.x() - (width()/2);
    int y = center.y() - (height()/2);
    center.setX(x);
    center.setY(y);
    move(center);


    // Выделяем память под окна студента и авторизации
    AWindow = new AuthorizationWindow();
    SWindow = new StudentWindow();
    //admWin = new AdminWin();

    // Связываем начальное окно и окно студента
    connect(SWindow, &StudentWindow::firstWindow, this, &MainWindow::show);

    // Связываем начальное окно и окно администратора
    connect(AWindow, &AuthorizationWindow::firstWindow, this, &MainWindow::show);

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
        this->close();
        AWindow->show();
    }

    if (ui->radioButton_2->isChecked()) {
        this->close();
        SWindow->show();
    }
}
