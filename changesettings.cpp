#include "changesettings.h"
#include "ui_changesettings.h"

ChangeSettings::ChangeSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeSettings)
{
    ui->setupUi(this);
}

ChangeSettings::~ChangeSettings()
{
    delete ui;
}
