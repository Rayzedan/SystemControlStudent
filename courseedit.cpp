#include "courseedit.h"
#include "ui_courseedit.h"

courseedit::courseedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::courseedit)
{
    ui->setupUi(this);
}

courseedit::~courseedit()
{
    delete ui;
}

// Закрываем окно
void courseedit::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit backToAdm();
}
