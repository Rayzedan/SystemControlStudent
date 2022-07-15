#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include "testforstudent.h"

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

signals:
    void firstWindow(); //Сигнал для соединения окна студента и окна авторизации
    void sendData(QString logFullName);

public slots:
    //void recieveData(QVariant variant);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

private:
    Ui::StudentWindow *ui;
    TestForStudent *testWindow;
    QSqlQueryModel *model;
    QSqlQueryModel *model_dep;
};

#endif // STUDENTWINDOW_H
