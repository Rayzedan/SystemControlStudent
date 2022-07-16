#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"


TestForStudent::TestForStudent(QVariantList takeData,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);

    db = new DataBase();

    countAnsw = 0;
    current_data = takeData;
    query = new QSqlQuery();

    query->exec("SELECT Name, Question, Variant1, Variant2, Variant3, Variant4, CorrectAnswer, "
                   "Chapters_id from Questions, Courses WHERE idCourse = Chapters_id ORDER BY RAND() LIMIT 3;");

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

//void TestForStudent::recieveData(QVariantList data)
//{
//    takeData.append(data);
//    qDebug() << takeData;
//}

void TestForStudent::on_pushButton_clicked()
{
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
     if (query->next()) {
        qDebug() << "зашли в цикл";
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString());
        ui->radioButton->setText(query->value("Variant1").toString());
        ui->radioButton_2->setText(query->value("Variant2").toString());
        ui->radioButton_3->setText(query->value("Variant3").toString());
        ui->radioButton_4->setText(query->value("Variant4").toString());
     }
     else
     {
         if (QMessageBox::Yes == QMessageBox::question(this,"Внимание","Завершить выполнение теста?"))
         {
             current_data.append(countAnsw);
             db->insertIntoTable(current_data);
             db->closeDataBase();
             this->close();
             qDebug() << "press yes";

         }
     }
}
