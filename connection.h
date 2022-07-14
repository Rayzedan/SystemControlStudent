#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>


 // Создаем одно соединение по умолчанию
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("ExaminationSystem");
    db.setUserName("root");
    db.setPassword("Zuban123");

    // Проверяем, получилось ли установить соединение
    bool ok = db.open();
    if (ok) {
            qDebug()<< "database open" ;
            return true;
    }
     else {
            qDebug()<< "error open database because" <<db.lastError().text();
            return false;
    }
}

#endif // CONNECTION_H
