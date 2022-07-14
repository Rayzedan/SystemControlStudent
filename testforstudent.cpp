#include "testforstudent.h"
#include "ui_testforstudent.h"

TestForStudent::TestForStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestForStudent)
{
    ui->setupUi(this);
}

TestForStudent::~TestForStudent()
{
    delete ui;
}

void TestForStudent::closeEvent(QCloseEvent *event)
{
    event->accept();
}
