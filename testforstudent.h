#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class TestForStudent;
}

class TestForStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestForStudent(QWidget *parent = nullptr);
    ~TestForStudent();

public slots:
    void recieveData(QString logFullName, QString depart);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();


private:
    Ui::TestForStudent *ui;
    QSqlQuery *query;
};

#endif // TESTFORSTUDENT_H
