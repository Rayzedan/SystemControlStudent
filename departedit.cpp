#include "departedit.h"
#include "ui_departedit.h"

departedit::departedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::departedit)
{
    ui->setupUi(this);
}

departedit::~departedit()
{
    delete ui;
}
