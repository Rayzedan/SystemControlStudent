#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

}

DataBase::~DataBase()
{

}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("ExaminationSystem");
    db.setUserName("root");
    db.setPassword("Zuban123");

    // Проверяем, получилось ли установить соединение
    bool ok = db.open();
    if (ok) {
            qDebug()<< "database open";
            return true;
    }
     else {
            qDebug()<< "error open database" << db.lastError().text();
            return false;
    }
}

bool DataBase::insertIntoTable(QVariantList data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Results (idResult, StudentName, Company, TestDuration, CorrectPercent, Credit, Courses_id) "
                  "VALUES (DEFAULT, :StudentName, :Company, :TestDuration, :CorrectPercent, :Credit, :Courses_id)");
    query.bindValue(":idResult", "DEFAULT");
    query.bindValue(":StudentName", data[0].toString());
    query.bindValue(":Company", data[1].toString());
    query.bindValue(":TestDuration", 40);
    query.bindValue(":CorrectPercent", data[4].toInt());
    query.bindValue(":Credit", 1);
    query.bindValue(":Courses_id", 1);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "Отправка";
        return true;
    }
    return false;
}

void DataBase::closeDataBase()
{
    db.close();
}
