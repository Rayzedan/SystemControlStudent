#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMessageBox>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    bool createNewConnection(QVariantList config);
    void closeDataBase();
    bool checkAnswer(const int sum, const QString nameChapter, QMap<QString, int>& dataAnswer, const int correctAnswer, QMap<int, int> &correctAnswers, const int ID, QMap<QString, int> &countAllAnswers);
    bool checkTextAnswer(QString answerUser ,const QString nameChapter, QMap<QString, int>& dataAnswerText, QString correctAnswerText, QMap<int, int> &correctAnswers, const int ID, QMap<QString, int> &countAllAnswers);
    bool checkData(const QString login, const QString password);
    void checkCorrectAnswer(QMap <int, int>& correctAnswer, const int ID);
    double sumAnswer(QMap <int, int>& correctAnswer);
    QMap<QString,int> mergeMap(QMap<QString, int>& dataAnswer, QMap<QString, int>& dataAnswerText);
    QString encryptPassword(const QString password);
    QString decodePassword(const QString password);
    bool createUser(QString login, QString password);
    void createDepart(QString name);
    void createCourse(QString name,QString description, QString Depart);
    void createCourseTime(QString time, QString course);
    void updateCourseTime(QString time, QString course);
    void updateDepart(QString name, QString newName);
    void updateCourse(QString name, QString newName, QString description, QString newDepart);
    void createChapter(QString name,QString number, QString Course);
    void createChapterCount(QString count, QString chapter);
    void updateChapterCount(QString count, QString chapter);
    void updateChapter(QString name, QString newName, QString number, QString newCourse);
    void createQuestion(QString type,QString question, QString variants, QString answer,QString chapter);
    void updateQuestion(QString type,QString question, QString variants, QString answer,QString chapter,QString oldquestionid);
    bool insertIntoTable(QVariantList data);
    QString filter(QString studentName, QString company, QString timeFirst, QString timeLast, QString precFirst, QString precLast, QString credit, QString CourseId);

private:

private:
    QSqlDatabase db;


};

#endif // DATABASE_H
