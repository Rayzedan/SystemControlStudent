#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationwindow.h"

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
    delete AWindow;
    delete SWindow;
}

// Кнопка выбора режим для пользователя
void MainWindow::on_pushButton_clicked()
{
    // Проверяем какая из кнопок для выбора пользователя нажата
    if (ui->radioButton->isChecked()) {

        AWindow = new AuthorizationWindow();
        admWindow = new AdminWin();
        qDebug() << admWindow;
        connect(admWindow, &AdminWin::secondWindow, this, &MainWindow::show);
        connect(this, &MainWindow::backToStart, AWindow, &AuthorizationWindow::takePoint);
        emit backToStart(admWindow);
        // Связываем начальное окно и окно авторизации        
        AWindow->show();
        this->close();
    }

    if (ui->radioButton_2->isChecked()) {

        SWindow = new StudentWindow();
        resWin = new FillResult();
        testWindow = new TestForStudent();
        qDebug() << resWin;
        // Связываем начальное окно и окно формы ввода данных студентом
        connect(SWindow, &StudentWindow::firstWindow, this, &MainWindow::show);
        connect(resWin, &FillResult::startWindow, this, &MainWindow::show);
        connect(this, &MainWindow::backFromResult, testWindow, &TestForStudent::takePoint);
        connect(this, &MainWindow::sendPoint, SWindow, &StudentWindow::takePoint);
        emit backFromResult(resWin);
        emit sendPoint(testWindow);
        SWindow->show();
        this->close();
    }
}
