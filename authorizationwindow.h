#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QCloseEvent>
#include <QWidget>
#include "database.h"
#include "adminwin.h"
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class AuthorizationWindow;
}


class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

public slots:
    void takePoint(AdminWin *admWin);
    void startMode(bool configMode);
signals:   
    void sendData(QString login);
    void firstWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::AuthorizationWindow *ui;
    DataBase *db;
    QSqlQueryModel *model;
    AdminWin *Awin;
    QString adminPassword = "WFRVXVJcaVRUTw==";
    bool mode = false;
};
#endif // AUTHORIZATIONWINDOW_H
