#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
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
    void backToStart(AdminWin *AdmWin); //Сигнал для соединения окна студента и окна авторизации

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DataBase db;
    StudentWindow *SWindow;
    AuthorizationWindow *AWindow;
    AdminWin *admWindow;
};

#endif // MAINWINDOW_H
