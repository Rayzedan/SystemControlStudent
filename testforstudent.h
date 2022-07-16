#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "database.h"

namespace Ui {
class TestForStudent;
}

class TestForStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestForStudent(QVariantList takeData, QWidget *parent = nullptr);
    ~TestForStudent();

public slots:
    //void recieveData(QVariantList data_send);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestForStudent *ui;
    QVariantList current_data;
    DataBase *db;
    QSqlQuery *query;
    int countAnsw;
};

#endif // TESTFORSTUDENT_H
