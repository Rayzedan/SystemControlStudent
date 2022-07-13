#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <authorizationwindow.h>
#include <studentwindow.h>
#include <QtGui>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    StudentWindow *SWindow;
    AuthorizationWindow *AWindow;
};

#endif // MAINWINDOW_H
