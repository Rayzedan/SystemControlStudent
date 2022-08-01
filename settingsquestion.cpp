#include "settingsquestion.h"
#include "ui_settingsquestion.h"

SettingsQuestion::SettingsQuestion(QVariantList data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsQuestion)
{
    ui->setupUi(this);
    qDebug()<<data;
}

SettingsQuestion::~SettingsQuestion()
{
    delete ui;
}
