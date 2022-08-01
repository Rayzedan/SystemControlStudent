#include "settingsquestion.h"
#include "ui_settingsquestion.h"

SettingsQuestion::SettingsQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsQuestion)
{
    ui->setupUi(this);
}

SettingsQuestion::~SettingsQuestion()
{
    delete ui;
}
