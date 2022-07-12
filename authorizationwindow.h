#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include "studentwindow.h"
#include "adminwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AuthorizationWindow; }
QT_END_NAMESPACE

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuthorizationWindow *ui;
    StudentWindow *SWindow;
    AdminWindow *AWindow;
};
#endif // AUTHORIZATIONWINDOW_H
