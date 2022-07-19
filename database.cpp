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
    // конфиг бд для админа
    QString host ="192.168.122.109";
    QString database = "ExaminationSystem";
    QString login = "Test";
    QString password = "123";

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL Server};""SERVER=%1;DATABASE=%2;UID=%3;\
    PWD=%4;").arg(host,database,login,password));


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


bool DataBase::checkData(const QString login, const QString password_user)
{
    QSqlQuery query;
    query.exec("SELECT Login, Password FROM Users WHERE Login='"+login+"' AND Password='"+encryptPassword(password_user)+"'");
    if (query.next()) {
        query.finish();
        return true;
    }
    else {
        QMessageBox :: warning (NULL, "Ошибка", "Неверное имя пользователя или пароль");
        return false;
    }
}

quint32 key =073;
QString DataBase::encryptPassword(const QString password)
{
    QByteArray arr(password.toUtf8());
    for(int i =0; i<arr.size(); i++)
         arr[i] = arr[i]^key;

     return QString::fromUtf8(arr.toBase64());
}

QString DataBase::decodePassword(const QString password)
{
    QByteArray arr = QByteArray::fromBase64(password.toUtf8());
    for(int i =0; i<arr.size(); i++)
        arr[i] =arr[i]^key;

    return QString::fromUtf8(arr);
}

bool DataBase::createUser(QString login, QString password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Users (Login, Password, Permissions) VALUES (:Login, :Password, :Permissions)");
    query.bindValue(":Login", login);
    query.bindValue(":Password", encryptPassword(password));
    query.bindValue(":Permissions", 1);
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
