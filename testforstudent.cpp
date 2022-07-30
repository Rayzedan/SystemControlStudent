#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"


TestForStudent::TestForStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);    
}

TestForStudent::~TestForStudent()
{
    delete ui;
}

// Закрываем окно
void TestForStudent::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void TestForStudent::on_pushButton_clicked()
{
    inputAnswer();
    // Проверяем наличие данных в бд
    if (query->next())
    {
        setData(query->value("TypeQuestion").toInt());
        sizeTest++;
    }
    else
    {
        // Если пользователь ответил на все вопросы выводим QMessageBox
        if (QMessageBox::Yes == QMessageBox::question(this,"Внимание","Завершить выполнение теста?"))
        {
            outputAnswer();
            timer->stop();
        }
    }
}


void TestForStudent::on_pushButton_2_clicked()
{
    countAnsw = 0;
    currentQuestId = query->value("idQuest").toInt();
    qDebug() << currentQuestId;
    if (query->previous() && currentQuestId!=firstQuestId)
    {
            setData(query->value("TypeQuestion").toInt());
            qDebug() << "Back " << currentQuestId;
    }
    else if (query->previous())
    {
        setData(query->value("TypeQuestion").toInt());
        qDebug() << "Back " << firstQuestId;
    }
}

void TestForStudent::dataCheckBox()
{
    // Проверяем какая из кнопок с ответом была нажата
    if (ui->checkBox->isChecked())
    {
        countAnsw+=1;
    }

    if (ui->checkBox_2->isChecked())
    {
        countAnsw+=2;
    }

    if (ui->checkBox_3->isChecked())
    {
        countAnsw+=4;
    }

    if (ui->checkBox_4->isChecked())
    {
        countAnsw+=8;
    }
    if (ui->checkBox->isChecked()==0 && ui->checkBox_2->isChecked()==0 && ui->checkBox_3->isChecked()==0 && ui->checkBox_4->isChecked()==0) {
        countAnsw=0;
    }
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
}

void TestForStudent::setData(const int typeQuestion)
{
    if (typeQuestion ==0)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label->setText(query->value("Name").toString());
        ui->textBrowser->setText(query->value("Question").toString()+ "?");
        ui->checkBox->setText(query->value("Variant1").toString());
        ui->checkBox_2->setText(query->value("Variant2").toString());
        ui->checkBox_3->setText(query->value("Variant3").toString());
        ui->checkBox_4->setText(query->value("Variant4").toString());
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->label->setText(query->value("Name").toString());
        ui->textBrowser->setText(query->value("Question").toString()+ "?");
        ui->textEdit->clear();
    }
}

void TestForStudent::updateTime()
{
    if (time.toString("hh:mm:ss")!="00:00:00")
    {
        time = time.addSecs(-1);
        timeResult = timeResult.addSecs(+1);
        ui->countdown->setText(time.toString("hh:mm:ss"));
        resultTime = time.toString("hh:mm:ss");
        qDebug() << timeResult.toString("hh:mm:ss");
    }
    else
    {
        inputAnswer();
        while (query-> next()) {
            inputAnswer();
            setData(query->value("TypeQuestion").toInt());
        }
            sizeTest++;
        QMessageBox::warning(this,"Внимание!", "Время вышло");

        outputAnswer();
        timer->stop();
    }
}

void TestForStudent::inputAnswer()
{
    countAnsw = 0;
    currentQuestId = query->value("idQuest").toInt();
    chapterName = query->value("Name").toString();
    int typeQuest = query->value("TypeQuestion").toInt();
    qDebug() << currentQuestId << " " << chapterName << " " << typeQuest;
    //db->countAllAnswer(currentQuestId, countAllAnswers);

    if (typeQuest ==0)
    {
        dataCheckBox();
        if (db->checkAnswer(countAnsw, chapterName, dataAnswer, query->value("CorrectAnswer").toInt(), correctAnswers, currentQuestId, countAllAnswers))
        {
            qDebug() << "true";
            correctAnswers[currentQuestId]++;
            countAnsw = 0;
        }
        else
        {
            qDebug() << "false";
            db->checkCorrectAnswer(correctAnswers,currentQuestId);
        }
    }
    else if  (typeQuest ==1)
    {
        if (db->checkTextAnswer(ui->textEdit->toPlainText(),chapterName, dataAnswerText,query->value("Variant1").toString(), correctAnswers, currentQuestId,countAllAnswers))
        {
            correctAnswers[currentQuestId]++;
            ui->textEdit->clear();
        }
        else
        {
            db->checkCorrectAnswer(correctAnswers,currentQuestId);
        }
    }
    qDebug() << currentQuestId << " " << correctAnswers[currentQuestId];
}

void TestForStudent::outputAnswer()
{
    testCorrectAnswer = db->sumAnswer(correctAnswers);
    //qDebug() << correctAnswers.size();
    credit = ((testCorrectAnswer/5.0) * 100.0);
    //qDebug() << credit;
    if (credit >= 40.0)
    {
        current_data.append(credit);
        current_data.append(1);
    }
    else
    {
        current_data.append(credit);
        current_data.append(0);
    }

    current_data.append(courseId);
    current_data.append(descriptionCourse);
    current_data.append(timeResult.toString("hh:mm:ss"));
    current_data.append(sizeTest);
    db->insertIntoTable(current_data);  // Отправка данных в бд
    connect(this, &TestForStudent::sendData,studentResult, &FillResult::takeData);
    emit sendData(countAllAnswers,current_data, db->mergeMap(dataAnswer, dataAnswerText));
    studentResult->show();
    this->close();
}

void TestForStudent::takePoint(FillResult *resWin)
{
    studentResult = resWin;
}

void TestForStudent::takeData(QVariantList data)
{
    query = new QSqlQuery();
    timer = new QTimer(this);
    sizeTest = 0;
    hour =0;
    min =0;
    countAnsw = 0;
    courseId =0;
    current_data = data;
    currentQuestId =0;

    ui->label_3->setText(current_data[3].toString());

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    query->exec("SELECT TOP 5 TimeCourses.Time, Chapters.Name, Question, Variant1, Variant2, Variant3, Variant4, CorrectAnswer, ChapterId, Courses.Id as idCourse, TypeQuestion, Questions.Id as idQuest, Description "
                   "from Questions, Courses, Chapters, TimeCourses"
                " WHERE Courses.Id = Chapters.CourseId AND Courses.Name = '"+current_data[3].toString()+"'"+" AND ChapterId = Chapters.Id AND Courses.Id = TimeCourses.CourseId "
                                                                                                                    "ORDER BY NEWID();");
    if (query->next())
    {
        firstQuestId = query->value("idQuest").toInt();
        descriptionCourse = query->value("Description").toString();
        courseId = query->value("idCourse").toInt();
        setData(query->value("TypeQuestion").toInt());
        min = query->value("Time").toInt();
    }    
    qDebug() << min;
    timerSettings();
    timeResult.setHMS(0,0,0);
    timer->start(1000);
    ui->countdown->setText(time.toString("hh:mm:ss"));
}

void TestForStudent::timerSettings()
{
    while (min >=60) {
        hour++;
        min-=60;
    }
    if (hour !=0) { time.setHMS(hour,min,0); }
    else { time.setHMS(0,min,0); }
    //qDebug() << time.hour();
}
