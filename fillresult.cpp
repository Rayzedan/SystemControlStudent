#include "fillresult.h"
#include "ui_fillresult.h"

FillResult::FillResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FillResult)
{
    ui->setupUi(this);
}

FillResult::~FillResult()
{
    delete ui;
}
