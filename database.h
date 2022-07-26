#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMessageBox>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
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
    void createCourse(QString name);
    void updateDepart(QString name, QString newName);
    void updateCourse(QString name, QString newName, QString description, QString newDepart);
    void updateChapter(QString name, QString newName, QString number, QString newCourse);
    bool insertIntoTable(QVariantList data);
    bool openDataBase();

private:

private:
    QSqlDatabase db;


};

#endif // DATABASE_H
