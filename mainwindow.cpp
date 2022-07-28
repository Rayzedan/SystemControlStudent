#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizationwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AWindow = new AuthorizationWindow();
    connect(this, &MainWindow::startConfigMode, AWindow, &AuthorizationWindow::startMode);
    configFile();
    ui->radioButton->setChecked(true);
    qDebug() << configMode;    
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

void MainWindow::configFile()
{
    QString fileName = "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    if (!QFile::exists(fileName)) {
       qDebug() << "FILE" << fileName <<" DON'T EXIST";
       settings.beginGroup("userSettings");
       settings.setValue("host", "");
       settings.setValue("database", "");
       settings.setValue("login", "");
       settings.setValue("password", "");
       settings.setValue("pathFile", "");
       settings.endGroup();       
    } else {             
        settings.beginGroup("userSettings");
        data.append(settings.value("host").toString());
        data.append(settings.value("database").toString());
        data.append(settings.value("login").toString());
        data.append(settings.value("password").toString());
        settings.endGroup();
       }
    configMode = db.createNewConnection(data);
    qDebug() << configMode;
    emit startConfigMode(configMode);
}
