#include "topicedit.h"
#include "ui_topicedit.h"

topicedit::topicedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::topicedit)
{
    ui->setupUi(this);
}

topicedit::~topicedit()
{
    delete ui;
}

// Закрываем окно
void topicedit::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit backToAdm();
}
