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

public slots:
    void takePoint(TestForStudent *testWin);

signals:
    void firstWindow(); //Сигнал для соединения окна студента и окна авторизации
    void sendData(QVariantList data);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

    void on_comboBox_2_currentTextChanged(QString arg1);

private:
    Ui::StudentWindow *ui;
    TestForStudent *testWindow;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QSqlQueryModel *model_dep;
};

#endif // STUDENTWINDOW_H
