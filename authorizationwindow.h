#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QCloseEvent>
#include "adminwindow.h"
#include <QWidget>

#include "adminwin.h"

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AuthorizationWindow *ui;
    AdminWindow *AdmWindow;
    QSqlQueryModel *model;
    AdminWin *Awin;

};
#endif // AUTHORIZATIONWINDOW_H
