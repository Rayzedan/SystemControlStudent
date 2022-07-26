#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "fillresult.h"
#include "testforstudent.h"
#include "authorizationwindow.h"
#include "studentwindow.h"
#include "adminwin.h"
#include <QtGui>
#include <QtWidgets>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void backToStart(AdminWin *AdmWin);  //Сигнал для соединения окна администрирования и окна авторизации
    void backFromResult (FillResult *resWindow);
    void sendPoint (TestForStudent *testWin);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DataBase db;
    StudentWindow *SWindow;
    AuthorizationWindow *AWindow;
    AdminWin *admWindow;
    TestForStudent *testWindow;
    FillResult *resWin;
};

#endif // MAINWINDOW_H
