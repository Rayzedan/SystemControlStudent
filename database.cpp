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
//    QString host ="DESKTOP-3NM09MJ\\\SQLEXPRESS";
//    QString database = "ExaminationSystem";
//    QString login = "Admin";
//    QString password = "Zuban123";
    QString host ="192.168.122.109,1234";
    QString database = "ExaminationSystem";
    QString login = "root";
    QString password = "12345";

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
    qDebug() << data;
    query.bindValue(":idResult", "DEFAULT"); // В таблице Results у поля idResult выставлен параметр AUTO_INCREMENT
    query.bindValue(":StudentName", data[0].toString());
    query.bindValue(":Company", data[1].toString());
    query.bindValue(":TestDuration", 40);
    query.bindValue(":CorrectPercent", data[4].toFloat());
    query.bindValue(":Credit", data[5].toInt());
    query.bindValue(":CourseId", data[6].toInt());

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

bool DataBase::checkAnswer(const int sum, const QString nameChapter, QMap<QString, int>& dataAnswer, const int correctAnswer)
{
    qDebug() << "зашли в checkAnswer";
    if (sum == correctAnswer)
    {
        qDebug() << "true";
        dataAnswer[nameChapter]++;
        return true;
    }
    else
    {
        if (dataAnswer.find(nameChapter)!=dataAnswer.end() && dataAnswer[nameChapter]!=0) {
        qDebug() << "false quest";
        dataAnswer[nameChapter]--;
        return false;
        }
    }

}

bool DataBase::checkTextAnswer(QString answerUser , const QString nameChapter, QMap<QString, int>& dataAnswerText, QString correctAnswerText)
{
    qDebug() << "зашли в checkTextAnswer";
    if (answerUser.toLower() == correctAnswerText.toLower())
    {
        qDebug() << "true";
        qDebug() << answerUser << " " << correctAnswerText;
        dataAnswerText[nameChapter]++;
        return true;
    }
    else
    {
        if (dataAnswerText.find(nameChapter)!=dataAnswerText.end() && dataAnswerText[nameChapter]!=0) {
        qDebug() << "false quest";
        dataAnswerText[nameChapter]--;
        return false;
        }
    }

}

double DataBase::sumAnswer(QMap <int, int>& correctAnswer)
{
    int count = 0;
    for (auto i: correctAnswer.keys()) {
        count+=correctAnswer.value(i);
        qDebug() << count;
    }

    return count;
}

void DataBase::checkCorrectAnswer(QMap<int, int> &correctAnswer, const int ID)
{
    if (correctAnswer.find(ID)!=correctAnswer.end() && correctAnswer[ID]!=0)
    {
        correctAnswer[ID]--;
    }
    else
    {
       correctAnswer[ID] = 0;
    }
}

// Метод закрытия бд
void DataBase::closeDataBase()
{
    db.close();
}
