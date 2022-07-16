#include "testforstudent.h"
#include "ui_testforstudent.h"
#include "studentwindow.h"

int sizeTest = 1;

TestForStudent::TestForStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);
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
    delete query;
}

// Закрываем окно
void TestForStudent::closeEvent(QCloseEvent *event)
{
    sizeTest = 0;
    event->accept();
}

void TestForStudent::recieveData(QString logFullName, QString depart)
{
    QString test = logFullName;
    QString test_2 = depart;
    qDebug() << test + " " + depart;
}

void TestForStudent::on_pushButton_clicked()
{
     if(sizeTest == query->size())
         QMessageBox::question(this,"Внимание","Завершить выполнение теста?");
     if (query->next()) {
        qDebug() << "зашли в цикл";
        sizeTest++;
        ui->label->setText(query->value("Name").toString());
        ui->label_2->setText(query->value("Question").toString());
        ui->radioButton->setText(query->value("Variant1").toString());
        ui->radioButton_2->setText(query->value("Variant2").toString());
        ui->radioButton_3->setText(query->value("Variant3").toString());
        ui->radioButton_4->setText(query->value("Variant4").toString());
     }
     qDebug() << sizeTest;
}


