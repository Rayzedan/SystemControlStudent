#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include<QMainWindow>
#include <adminwindow.h>
#include <QWidget>

namespace Ui {
class AuthorizationWindow;
}


class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

signals:
    void firstWindow(); //Сигнал для соединения окна начального входа и окна авторизации

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AuthorizationWindow *ui;
    AdminWindow *AdmWindow;
};
#endif // AUTHORIZATIONWINDOW_H
