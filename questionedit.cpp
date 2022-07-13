#include "questionedit.h"
#include "ui_questionedit.h"
#include "QMessageBox"

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

void questionedit::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Тест"){
        QMessageBox::information(this,"Выбор1","Выводим чекбоксы");
    }
    else if (arg1 == "Свободный ввод"){
        QMessageBox::information(this,"Выбор2","Выводим простынь");
    }
}

