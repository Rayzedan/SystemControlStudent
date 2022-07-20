#include "fillresult.h"
#include "ui_fillresult.h"
#include "studentwindow.h"

FillResult::FillResult (QVariantList result, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FillResult)
{
    ui->setupUi(this);
    take_data = result;
    ui->name->setText(take_data[0].toString());
    ui->company->setText(take_data[1].toString());
    ui->result->setText(take_data[5].toString());
    ui->course->setText(take_data[6].toString());


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

