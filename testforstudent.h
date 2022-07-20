#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "database.h"
#include "QTime"
#include "QTimer"
#include "fillresult.h"

namespace Ui {
class TestForStudent;
}

class TestForStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestForStudent(QVariantList takeData, QWidget *parent = nullptr);
    ~TestForStudent();

    //void inputAnswer(const ind ID);
    void setData(const int typeQuestion);
    void dataCheckBox();

public slots:


protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateTime();

private:
    Ui::TestForStudent *ui;
    FillResult *studentResult;
    QMap <int, int> correctAnswers;
    QMap <QString, int> dataAnswer;
    QMap <QString, int> dataAnswerText;
    QString resultTime;
    QTime time;
    QTimer *timer;
    QVariantList current_data;
    DataBase *db;
    QSqlQuery *query;
    QString chapterName;
    QString descriptionCourse;
    double testCorrectAnswer;
    double credit;
    int countAnsw;
    int courseId;
    int currentQuestId;
    double sizeTest;
};

#endif // TESTFORSTUDENT_H
