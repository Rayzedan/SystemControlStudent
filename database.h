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
    bool checkData(const QString login, const QString password);
    bool insertIntoTable(QVariantList data);
    bool openDataBase();

private:

private:
    QSqlDatabase db;


};

#endif // DATABASE_H