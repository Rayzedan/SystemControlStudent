#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

}

DataBase::~DataBase()
{

}

// Метод для открытия БД
bool DataBase::openDataBase()
{
    QString host = "TUNAKA";
    QString database = "ExaminationSystem";

    db = QSqlDatabase::addDatabase("QODBC");
    //db.setHostName("127.0.0.1");
    //db.setPort(3306);
    //db.setDatabaseName("ExaminationSystem");
    //db.setDatabaseName( "DRIVER={SQL Server};Server=TUNAKA;Database=ExaminationSystem;Trusted_Connection=yes" );
    db.setDatabaseName(QString("DRIVER={SQL Server};""SERVER=%1;DATABASE=%2;Trusted_Connection=yes;").arg(host,database));
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

// Метод для отправки данных в бд
bool DataBase::insertIntoTable(QVariantList data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Results (StudentName, Company, TestDuration, CorrectPercent, Credit, CourseId) "
                  "VALUES (:StudentName, :Company, :TestDuration, :CorrectPercent, :Credit, :CourseId)");
    query.bindValue(":idResult", "DEFAULT"); // В таблице Results у поля idResult выставлен параметр AUTO_INCREMENT
    query.bindValue(":StudentName", data[0].toString());
    query.bindValue(":Company", data[1].toString());
    query.bindValue(":TestDuration", 40);
    query.bindValue(":CorrectPercent", data[4].toFloat());
    query.bindValue(":Credit", data[5].toInt());
    query.bindValue(":CourseId", 1);

    // Проверяем успешно ли отправились данные
    if(!query.exec()){
        qDebug() << "error insert into ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "Отправка ";
        return true;
    }
    return false;
}

// Метод закрытия бд
void DataBase::closeDataBase()
{
    db.close();
}
