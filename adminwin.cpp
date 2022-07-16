#include "adminwin.h"
#include "ui_adminwin.h"


AdminWin::AdminWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWin)
{
    ui->setupUi(this);

    model_res = new QSqlQueryModel();
    model_res->setQuery("Select Courses_id, StudentName, Company, Credit, TestDuration, CorrectPercent from Results");
    ui->tableView_2->setModel(model_res);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

AdminWin::~AdminWin()
{
    delete ui;
    delete model_res;
}

void AdminWin::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Тест") {
        //QMessageBox::information(this,"Выбор1","Выводим чекбоксы");
        ui->stackedWidget->setCurrentIndex(1);

    }
    else if (arg1 == "Свободный ввод") {
        //QMessageBox::information(this,"Выбор2","Выводим простынь");
        ui->stackedWidget->setCurrentIndex(0);
    }
}

// Закрываем окно
void AdminWin::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit secondWindow();
}
