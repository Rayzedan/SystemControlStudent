#include "adminwin.h"
#include "ui_adminwin.h"

AdminWin::AdminWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWin)
{
    ui->setupUi(this);
}

AdminWin::~AdminWin()
{
    delete ui;
}

void AdminWin::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Тест"){
        //QMessageBox::information(this,"Выбор1","Выводим чекбоксы");
        ui->stackedWidget->setCurrentIndex(1);

    }
    else if (arg1 == "Свободный ввод"){
        //QMessageBox::information(this,"Выбор2","Выводим простынь");
        ui->stackedWidget->setCurrentIndex(0);
    }
}

