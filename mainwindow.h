#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authorizationwindow.h"
#include "studentwindow.h"
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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    StudentWindow *SWindow;
    AuthorizationWindow *AWindow;
};

#endif // MAINWINDOW_H
