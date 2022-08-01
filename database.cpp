#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

}

DataBase::~DataBase()
{

}

// Метод для открытия БД
bool DataBase::createNewConnection(QVariantList config)
{
    // конфиг бд для админа
    QString host =config[0].toString();
    QString database = config[1].toString();
    QString login = decodePassword(config[2].toString());
    QString password = decodePassword(config[3].toString());
    qDebug() << host << " " << database << " " << login << " " << password;
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
    query.bindValue(":TestDuration", data[8].toInt());
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

void DataBase::createDepart(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Departments (name) VALUES (:name)");
    query.bindValue(":name",name);
    if (!query.exec()) {
        qDebug() << "error insert into ";
        qDebug() << query.lastError().text();
    } else qDebug() << "Создание нового департамента ";
}

void DataBase::updateDepart(QString name, QString newName)
{
    QSqlQuery query;
    query.prepare("UPDATE Departments SET Name = '"+newName+"'WHERE Name ='"+name+"';");
    if(!query.exec()){
        qDebug() << "error update into ";
        qDebug() << query.lastError().text();
    } else
    {
        qDebug() << "Изменение департамента";
    }
}
void DataBase::createCourse(QString name,QString description, QString Depart){
    QSqlQuery query;
    query.prepare("SELECT Id From Departments WHERE Name = '"+Depart+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("Insert Into Courses(Name, Description, DepartmentId) Values ('"+name+"','"+description+"',"+id+");");
};

void DataBase::createCourseTime(QString time, QString course){
    QSqlQuery query;
    query.prepare("SELECT Id From Courses WHERE Name = '"+course+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("Insert Into TimeCourses(Time,CourseId) Values ("+time+","+id+");");
};
void DataBase::updateCourseTime(QString time, QString course){
    QSqlQuery query;
    query.prepare("SELECT Id From Courses WHERE Name = '"+course+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("UPDATE TimeCourses Set Time="+time+" Where CourseId="+id+";");
};

void DataBase::updateCourse(QString name, QString newName, QString description, QString newDepart)
{
    QSqlQuery query;
    query.prepare("SELECT Id From Departments WHERE Name = '"+newDepart+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    if (newName == "" && description == "")
    {
        query.prepare("UPDATE Courses SET DepartmentId = "+id+" WHERE Name ='"+name+"';");
    }
    else if (newName == "")
    {
        query.prepare("UPDATE Courses SET DepartmentId = "+id+", Description = '"+description+"' WHERE Name ='"+name+"';");
    }
    else
    {
        query.prepare("UPDATE Courses SET Name= '"+newName+"', DepartmentId = "+id+", Description = '"+description+"' WHERE Name ='"+name+"';");
    }
    if(!query.exec()){
        qDebug() << "error update into ";
        qDebug() << query.lastError().text();
    } else
    {
        qDebug() << "Изменение курса";
    }
}

void DataBase::createChapter(QString name,QString number, QString Course){
    QSqlQuery query;
    query.exec("SELECT Id From Courses WHERE Name = '"+Course+"';");
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("Insert Into Chapters(Name,Number,CourseId) Values ('"+name+"',"+number+","+id+");");
};

void DataBase::createChapterCount(QString count, QString chapter){
    QSqlQuery query;
    query.prepare("SELECT Id From Chapters WHERE Name = '"+chapter+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("Insert Into CountChapters(Count,ChapterId) Values ("+count+","+id+");");
};

void DataBase::updateChapterCount(QString count, QString chapter){
    QSqlQuery query;
    query.prepare("SELECT Id From Chapters WHERE Name = '"+chapter+"';");
    query.exec();
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    query.exec("Update CountChapters SET Count="+count+" Where ChapterId="+id+";");
};


void DataBase::updateChapter(QString name, QString newName, QString number, QString newCourse)
{
    QSqlQuery query;    
    QString request = "SELECT Id From Courses WHERE Name = '"+newCourse+"';";
    query.prepare(request);
    query.exec();
    query.next();
    QString id = query.value("Id").toString();    

    if (newName == "" && number == "")
    {
        query.prepare("UPDATE Chapters SET CourseId = "+id+" WHERE Name ='"+name+"';");
    }
    else if (newName == "")
    {
        query.prepare("UPDATE Chapters SET CourseId = "+id+", Number = "+number+" WHERE Name ='"+name+"';");
    }
    else
    {
        query.prepare("UPDATE Chapters SET Name= '"+newName+"', CourseId = "+id+", Number = "+number+" WHERE Name ='"+name+"'");
    }
    if(!query.exec()){
        qDebug() << "error update into ";
        qDebug() << query.lastError().text();
    } else
    {
        qDebug() << "Изменение раздела";
    }
}

void DataBase::createQuestion(QString type,QString question, QString variants, QString answer,QString chapter){
    qDebug() << "Добавление вопроса";
    QSqlQuery query;
    query.exec("SELECT Id From Chapters WHERE Name = '"+chapter+"';");
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    QList variant = variants.split("; ");
    QString typeQuestion;
    if (type=="Тестовый"){
        typeQuestion ="0";
    } else{
        typeQuestion ="1";
    }
    query.prepare("Insert Into Questions(TypeQuestion,Question,Variant1,Variant2,Variant3,Variant4,CorrectAnswer, ChapterId) Values ("+typeQuestion+\
                  ",'"+question+"','"+variant[0]+"','"+variant[1]+"','"+variant[2]+"','"+variant[3]+"',"+answer+","+id+")");
    query.exec();
};

void DataBase::updateQuestion(QString oldquestion,QString question, QString variants, QString answer,QString chapter){
    QSqlQuery query;
    query.exec("SELECT Id From Chapters WHERE Name = '"+chapter+"'");
    query.next();
    QString id = query.value("Id").toString();
    query.clear();
    QList variant = variants.split("; ");
    qDebug()<<"Запрос";
    query.clear();
    query.exec("UPDATE Questions SET Question = '"+question+"', Variant1 = '"+variant[0]+"', Variant2 = '"+variant[1]+"', Variant3 = '"+variant[2]+"', Variant4 = '"+variant[3]+"', CorrectAnswer = "+answer+", ChapterId = "+id+" Where Question = '"+oldquestion+"';");
};

bool DataBase::checkAnswer(const int sum, const QString nameChapter, QMap<QString, int>& dataAnswer, const int correctAnswer, QMap<int, int> &correctAnswers, const int ID, QMap<QString, int> &countAllAnswers)
{
    if (!correctAnswers.count(ID))
    {
        countAllAnswers[nameChapter]++;
        qDebug() << "ID = 0 CHECK";
        if (sum == correctAnswer) {
            qDebug() << "true";
            dataAnswer[nameChapter]++;
            qDebug() << nameChapter << " " << dataAnswer[nameChapter];
            return true;
        }
        else if (!dataAnswer.count(nameChapter))
        {
            dataAnswer[nameChapter] = 0;
            return false;
        }
    }
    else
    {
        qDebug() << "ID = 1 CHECK";
        if (sum == correctAnswer && correctAnswers[ID]!=1) {
            qDebug() << "true";
            dataAnswer[nameChapter]++;
            qDebug() << nameChapter << " " << dataAnswer[nameChapter];
            return true;
        }
        else
        {
            if (dataAnswer.count(nameChapter) && correctAnswers[ID]!=0) {
                qDebug() << "false quest";
                dataAnswer[nameChapter]--;
                qDebug() << nameChapter << " " << dataAnswer[nameChapter];
                return false;
            }
            else
            {
//                dataAnswer[nameChapter] = 0;
//                qDebug() << nameChapter << " " << dataAnswer[nameChapter];
            }
        }
        return false;
    }
    return false;
}

bool DataBase::checkTextAnswer(QString answerUser, const QString nameChapter, QMap<QString, int>& dataAnswerText, QString correctAnswerText, QMap<int, int> &correctAnswers, const int ID, QMap<QString, int> &countAllAnswers)
{
    qDebug() << "зашли в checkTextAnswer";
    if (!correctAnswers.count(ID))
    {
        countAllAnswers[nameChapter]++;
        qDebug() << "ID = 0 CHECK";
        if (answerUser.toLower() == correctAnswerText.toLower()) {
            qDebug() << "true";
            dataAnswerText[nameChapter]++;
            qDebug() << nameChapter << " " << dataAnswerText[nameChapter];
            return true;
        }
        else { return false; }
    }
    else
    {
        qDebug() << "ID = 1 CHECK";
        if (answerUser.toLower() == correctAnswerText.toLower() && correctAnswers[ID]!=1) {
            qDebug() << "true";
            dataAnswerText[nameChapter]++;
            qDebug() << nameChapter << " " << dataAnswerText[nameChapter];
            return true;
        }
        else
        {
            if (dataAnswerText.count(nameChapter)&& correctAnswers[ID]!=0) {
                qDebug() << "false quest";
                dataAnswerText[nameChapter]--;
                qDebug() << nameChapter << " " << dataAnswerText[nameChapter];
                return false;
            }
        }
        return false;
    }
    return false;
}

double DataBase::sumAnswer(QMap <int, int>& correctAnswer)
{
    int count = 0;
    qDebug() << "ответы";
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

QMap<QString,int> DataBase::mergeMap(QMap<QString, int> &dataAnswer, QMap<QString, int> &dataAnswerText)
{
    QMap<QString,int> resultMap;
    foreach (const QString key, dataAnswer.keys()) {
        qDebug() << "dataAnswer";
        qDebug() << key << " " << dataAnswer[key];
    }
    foreach (const QString key, dataAnswerText.keys()) {
        qDebug() << "dataAnswerText";
        qDebug() << key << " " << dataAnswerText[key];
    }
    foreach (const QString key, dataAnswer.keys()) {
        if (dataAnswerText.contains(key)) {
            resultMap[key] = dataAnswerText[key] + dataAnswer[key];
            qDebug() << key << " " << resultMap[key];
        }
        else
        {
            resultMap[key] = dataAnswer[key];
            qDebug() << key << " " << resultMap[key];
        }
    }
    return resultMap;
}


// Метод закрытия бд
void DataBase::closeDataBase()
{
    qDebug() << "close database";
    db.close();
}
