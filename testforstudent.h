#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QWidget>
#include <QCloseEvent>
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
    explicit TestForStudent(QWidget *parent = nullptr);
    ~TestForStudent();

    //void inputAnswer(const ind ID);
    void setData(const int typeQuestion);
    void dataCheckBox();
    void inputAnswer();
    void outputAnswer();

public slots:
    void takePoint(FillResult *resWin);
    void takeData(QVariantList data);

signals:
    void sendData(QMap<QString, int> countAllAnswers, QVariantList result, QMap<QString, int> themes);

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
    QMap <QString,int> countAllAnswers;
    QString resultTime;
    QTime time;
    QTimer *timer;
    QVariantList current_data;
    DataBase *db;
    QSqlQuery *query;
    QString chapterName;
    QString descriptionCourse;
    int firstQuestId;
    double testCorrectAnswer;
    double credit;
    int countAnsw;
    int courseId;
    int currentQuestId;
    double sizeTest;
};

#endif // TESTFORSTUDENT_H
