#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMessageBox>
#include <QSql>
#include <QSqlQuery>
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
    bool insertIntoTable(QVariantList data);
    bool openDataBase();

private:

private:
    QSqlDatabase db;


};

#endif // DATABASE_H
