#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthorizationWindow; }
QT_END_NAMESPACE

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::AuthorizationWindow *ui;
};
#endif // AUTHORIZATIONWINDOW_H
