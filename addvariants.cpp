#include "addvariants.h"
#include "ui_addvariants.h"


AddVariants::AddVariants(QVariantList data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVariants)
{
    ui->setupUi(this);
    query = new QSqlQuery();
    qDebug()<<"ДОБАВЛЕНИЕ";

    if (data[0].toString()=="Курс"){
        helpQ = new QSqlQuery();
        helpQ->exec("select id from Departments where name='"+data[3].toString()+"';");
        helpQ->next();
        QString id = helpQ->value("Id").toString();
        ui->label->setText(data[2].toString());
        ui->label_4->setText(data[1].toString());
        ui->label_2->setText(data[0].toString());
        query->prepare("Insert into Courses(name,description,departmentid)\
                       Values (:name,:next_val,"+id+")");

    } else if (data[0].toString()=="Тема"){
        helpQ = new QSqlQuery();
        helpQ->exec("select id from Courses where name='"+data[3].toString()+"';");
        helpQ->next();
        QString id = helpQ->value("Id").toString();
        ui->label->setText(data[2].toString());
        ui->label_4->setText(data[1].toString());
        ui->label_2->setText(data[0].toString());
        query->prepare("Insert into Chapters(name,number,CourseId)\
                       Values (:name,:next_val,"+id+")");
    }
}

AddVariants::~AddVariants()
{
    delete ui;
}

void AddVariants::on_pushButton_clicked()
{

    QString value = ui->lineEdit->text();
    QString Next_value = ui->lineEdit_2->text();
    if (Next_value !=""){
        query->bindValue(":name", value);
        query->bindValue(":next_val", Next_value);
    } else {
        query->bindValue(":name", value);
    }
    qDebug()<< query->lastError().text();
    query->exec();
    this->close();
}

