#include "addvariants.h"
#include "ui_addvariants.h"

AddVariants::AddVariants(QVariantList data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVariants)
{
    ui->setupUi(this);
    qDebug()<<data;
    QSqlQuery query;
    if (data[0].toString()=="департамент") {
       ui->label_2->setText(data[0].toString());
       query.prepare("Insert into Departments(name) Values (:name)");
    } else if (data[0].toString()=="курс"){
        ui->label_2->setText(data[0].toString());
        query.prepare("Insert into Courses(Courses.name,description,Departments.name)\
 Values (:name1,:description,:name2) where Departments.Id=Courses.DepartmentId");
    } else if (data[0].toString()=="тему"){
        ui->label_2->setText(data[0].toString());
        query.prepare("Insert into Chapters(Chapters.name,number,Courses.name)\
 Values (:name1,:number,:name2) where Courses.Id=Chapters.CourseId");
    }
}

AddVariants::~AddVariants()
{
    delete ui;
}

void AddVariants::on_pushButton_clicked()
{
    QString value = ui->lineEdit->text();
}

