#include "questionedit.h"
#include "ui_questionedit.h"
#include "QMessageBox"

questionedit::questionedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::questionedit)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentText("Тест");

    //stackedWidget = new QStackedWidget(this);
    //stackedWidget->addWidget(ui->TextPage);
    //stackedWidget->addWidget(ui->TestPage);
    //setCentralWidget(stackedWidget);

}

questionedit::~questionedit()
{
    delete ui;
}

void questionedit::on_comboBox_currentTextChanged(const QString &arg1)
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

