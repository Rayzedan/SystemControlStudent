#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>
#include <QWidget>
<<<<<<< HEAD
#include "testforstudent.h"
=======
#include <QSqlQueryModel>
>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)

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

private slots:
    void on_pushButton_3_clicked();

<<<<<<< HEAD
=======

>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)
    void on_pushButton_clicked();

private:
    Ui::StudentWindow *ui;
<<<<<<< HEAD
    TestForStudent *testWindow;
=======
    QSqlQueryModel *model;
    QSqlQueryModel *model_dep;
>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)
};

#endif // STUDENTWINDOW_H
