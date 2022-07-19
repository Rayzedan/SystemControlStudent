#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"

TestForStudent::TestForStudent(QVariantList takeData,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);

    countAnsw = 0;
    current_data = takeData;
    query = new QSqlQuery();

    query->exec("SELECT Name, Question, Variant1, Variant2, Variant3, Variant4, CorrectAnswer, "
                   "ChapterId from Questions, Courses WHERE Courses.Id = ChapterId ORDER BY RAND();");

    // Добавляем из бд первую строчку и сразу отображаем её
    if (query->next()) {
       qDebug() << "зашли в цикл";
       ui->label->setText(query->value("Name").toString());
       ui->label_2->setText(query->value("Question").toString());
       ui->radioButton->setText(query->value("Variant1").toString());
       ui->radioButton_2->setText(query->value("Variant2").toString());
       ui->radioButton_3->setText(query->value("Variant3").toString());
       ui->radioButton_4->setText(query->value("Variant4").toString());
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
     // Проверяем какая из кнопок с ответом была нажата
     if (ui->radioButton->isChecked() && query->value("CorrectAnswer").toInt() == 1)
     {
         countAnsw++;
     }
     if (ui->radioButton_2->isChecked() && query->value("CorrectAnswer").toInt() == 2)
     {
         countAnsw++;
     }
     if (ui->radioButton_3->isChecked() && query->value("CorrectAnswer").toInt() == 3)
     {
         countAnsw++;
     }
     if (ui->radioButton_4->isChecked() && query->value("CorrectAnswer").toInt() == 4)
     {
         countAnsw++;
     }

     // Проверяем наличие данных в бд
     if (query->next()) {
        qDebug() << "зашли в цикл";
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString() + "?");
        ui->radioButton->setText(query->value("Variant1").toString());
        ui->radioButton_2->setText(query->value("Variant2").toString());
        ui->radioButton_3->setText(query->value("Variant3").toString());
        ui->radioButton_4->setText(query->value("Variant4").toString());
     }
     else
     {
         // Если пользователь ответил на все вопросы выводим QMessageBox
         if (QMessageBox::Yes == QMessageBox::question(this,"Внимание","Завершить выполнение теста?"))
         {
             qDebug() << "press yes";
             double credit = countAnsw/query->size() * 100.0;
             current_data.append(countAnsw);
             if (credit >= 40.0)
                 current_data.append(1);
             else
                 current_data.append(0);
             db->insertIntoTable(current_data); // Отправка данных в бд
             db->closeDataBase();
             this->close();
         }
     }
}

void TestForStudent::on_pushButton_2_clicked()
{
    if (query->seek(query->at()-1)) {
        qDebug() << "зашли в цикл";
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString() + "?");
        ui->radioButton->setText(query->value("Variant1").toString());
        ui->radioButton_2->setText(query->value("Variant2").toString());
        ui->radioButton_3->setText(query->value("Variant3").toString());
        ui->radioButton_4->setText(query->value("Variant4").toString());
    }
}

