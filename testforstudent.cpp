#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"

TestForStudent::TestForStudent(QVariantList takeData, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);
    query = new QSqlQuery();
    timer = new QTimer(this);
    int time1 = 10;
    time.setHMS(0,time1,0);
    sizeTest = 0;
    countAnsw = 0;
    courseId =0;
    current_data = takeData;
    currentQuestId =0;

    ui->label_3->setText(current_data[3].toString());

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    query->exec("SELECT TOP 5 Chapters.Name, Question, Variant1, Variant2, Variant3, Variant4, CorrectAnswer, ChapterId, CourseId, TypeQuestion, Questions.Id, Description "
                   "from Questions, Courses, Chapters"
                " WHERE Courses.Id = Chapters.CourseId AND Courses.Name = '"+current_data[3].toString()+"'"+" AND ChapterId = Chapters.Id "
                                                                                                                    "ORDER BY NEWID();");
    if (query->next())
    {
        firstQuestId = query->value("Id").toInt();
        descriptionCourse = query->value("Description").toString();
        courseId = query->value("CourseId").toInt();
        setData(query->value("TypeQuestion").toInt());        
    }
    timer ->start(1000);
    ui->countdown->setText(time.toString("hh:mm:ss"));
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
        }
    }
}


void TestForStudent::on_pushButton_2_clicked()
{
    countAnsw = 0;
    currentQuestId = query->value("Id").toInt();
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
    if (time.toString("m:ss")!="0:50")
    {
        time = time.addSecs(-1);
        ui->countdown->setText(time.toString("m:ss"));
        resultTime = time.toString("m:ss");
        //qDebug() << resultTime;
    }
    else
    {
        while (query-> next())
            sizeTest++;
        QMessageBox::warning(this,"Внимание!", "Время вышло");
        inputAnswer();
        outputAnswer();
        timer->stop();
    }
}

void TestForStudent::inputAnswer()
{
    countAnsw = 0;
    currentQuestId = query->value("Id").toInt();
    chapterName = query->value("Name").toString();
    int typeQuest = query->value("TypeQuestion").toInt();

    //db->countAllAnswer(currentQuestId, countAllAnswers);

    if (typeQuest ==0)
    {
        dataCheckBox();
        if (db->checkAnswer(countAnsw, chapterName, dataAnswer, query->value("CorrectAnswer").toInt(), correctAnswers, currentQuestId, countAllAnswers))
        {
            correctAnswers[currentQuestId]++;
            countAnsw = 0;
        }
        else
        {
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
    credit = ((testCorrectAnswer/correctAnswers.size()) * 100.0);
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
    current_data.append(time.toString("m:ss"));
    current_data.append(sizeTest);
    db->insertIntoTable(current_data); // Отправка данных в бд
    studentResult = new FillResult(countAllAnswers,current_data, db->mergeMap(dataAnswer, dataAnswerText));
    studentResult->show();
    this->close();
}
