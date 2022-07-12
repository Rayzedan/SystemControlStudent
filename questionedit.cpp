#include "questionedit.h"
#include "ui_questionedit.h"

questionedit::questionedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::questionedit)
{
    ui->setupUi(this);
}

questionedit::~questionedit()
{
    delete ui;
}
