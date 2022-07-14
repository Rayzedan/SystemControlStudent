#include "resultswindow.h"
#include "ui_resultswindow.h"


ResultsWindow::ResultsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsWindow)
{
    ui->setupUi(this);
    model_res = new QSqlQueryModel();
    model_res->setQuery("Select Courses_id, StudentName, Company, Credit, TestDuration, CorrectPercent from Results");
    ui->tableView->setModel(model_res);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ResultsWindow::~ResultsWindow()
{
    delete ui;
}
