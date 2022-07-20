#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"

TestForStudent::TestForStudent(QVariantList takeData, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);

    query = new QSqlQuery();

    countAnsw = 0;
    courseId =0;
    current_data = takeData;
    currentQuestId =0;

    query->exec("SELECT Chapters.Name, Question, Variant1, Variant2, Variant3, Variant4, CorrectAnswer, ChapterId, CourseId, TypeQuestion, Questions.Id "
                   "from Questions, Courses, Chapters"
                " WHERE Courses.Id = Chapters.CourseId AND Courses.Name = '"+current_data[3].toString()+"'"+" AND ChapterId = Chapters.Id;");
                                                                                                                    /*"ORDER BY NEWID();");*/
    if (query->next())
    {
        courseId = query->value("CourseId").toInt();
        setData(query->value("TypeQuestion").toInt());
    }
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
    countAnsw = 0;
    currentQuestId = query->value("Id").toInt();
    chapterName = query->value("Name").toString();

    if (query->value("TypeQuestion").toInt() ==1)
    {
        dataCheckBox();
        if (db->checkAnswer(countAnsw, chapterName, dataAnswer, query->value("CorrectAnswer").toInt()))
        {
            correctAnswer[currentQuestId]++;
            countAnsw = 0;
        }
        else
        {
            db->checkCorrectAnswer(correctAnswer,currentQuestId);
        }
    }
    else
    {
        if (db->checkTextAnswer(ui->textEdit->toPlainText(),chapterName, dataAnswerText,query->value("Variant1").toString()))
        {
            correctAnswer[currentQuestId]++;
            ui->textEdit->clear();
        }
        else
        {
            db->checkCorrectAnswer(correctAnswer,currentQuestId);
        }
    }
    // Проверяем наличие данных в бд
    if (query->next())
    {
        setData(query->value("TypeQuestion").toInt());
    }
    else
    {
        // Если пользователь ответил на все вопросы выводим QMessageBox
        if (QMessageBox::Yes == QMessageBox::question(this,"Внимание","Завершить выполнение теста?"))
        {
            double testCorrectAnswer = db->sumAnswer(correctAnswer);
            qDebug() << correctAnswer.size();
            double credit = ((testCorrectAnswer/correctAnswer.size()) * 100.0);
            qDebug() << credit;
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
            db->insertIntoTable(current_data); // Отправка данных в бд
            studentResult = new FillResult(current_data);
            studentResult->show();
            this->close();
        }
    }
}


void TestForStudent::on_pushButton_2_clicked()
{
    countAnsw = 0;
    if (query->previous())
    {
        setData(query->value("TypeQuestion").toInt());
    }
}

void TestForStudent::dataCheckBox()
{
    // Проверяем какая из кнопок с ответом была нажата
    if (ui->checkBox->isChecked())
    {
        countAnsw+=2;
    }

    if (ui->checkBox_2->isChecked())
    {
        countAnsw+=4;
    }

    if (ui->checkBox_3->isChecked())
    {
        countAnsw+=8;
    }

    if (ui->checkBox_4->isChecked())
    {
        countAnsw+=16;
    }
}

void TestForStudent::setData(const int typeQuestion)
{
    if (typeQuestion ==1)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString()+ "?");
        ui->checkBox->setText(query->value("Variant1").toString());
        ui->checkBox_2->setText(query->value("Variant2").toString());
        ui->checkBox_3->setText(query->value("Variant3").toString());
        ui->checkBox_4->setText(query->value("Variant4").toString());
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString()+ "?");
        ui->textEdit->clear();
    }
}
