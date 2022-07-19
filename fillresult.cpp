#include "fillresult.h"
#include "ui_fillresult.h"
FillResult::FillResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FillResult)
{
    ui->setupUi(this);
    query = new QSqlQuery();

    query->exec("Select StudentName, Company, Credit,TestDuration, CorrectPercent,\
    name from Results inner join Courses on Results.CourseId=Courses.Id where Results.Id=1;");

    if (query->next()) {
        qDebug() << "зашли в цикл";
        ui->name->setText(query->value("StudentName").toString());
        ui->company->setText(query->value("Company").toString());
        ui->credit->setText(query->value("Credit").toString());
        ui->time->setText(query->value("TestDuration").toString());
        ui->result->setText(query->value("CorrectPercent").toString());
        ui->course->setText(query->value("name").toString());
}
}

FillResult::~FillResult()
{
    delete ui;
}

void FillResult::on_pushButton_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);

    if(dialog.exec() == QDialog::Accepted) {

    }
}

