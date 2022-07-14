#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    QCommonStyle style;
    //Выделяем память под каждый из разделов
    questForm = new questionedit();
    departForm = new departedit();
    courseForm = new courseedit();
    topicForm = new topicedit();
    baseForm = new BaseWindow();
    resultForm = new ResultsWindow();
    ui->setupUi(this);
    ui->pushButton_4->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

// Кнопка для создания задания
void AdminWindow::on_toolButton_clicked()
{
    questForm->show();
}

// Кнопка для создания департамента
void AdminWindow::on_toolButton_3_clicked()
{
    departForm->show();
}

// Кнопка для создания курса
void AdminWindow::on_toolButton_4_clicked()
{
   courseForm->show();
}

// Кнопка для создания темы
void AdminWindow::on_ButDeppart_clicked()
{
   topicForm->show();
}

// Кнопка возврата в окно авторизации
void AdminWindow::on_pushButton_4_clicked()
{
    this->destroy();
    emit backToAuth();
}


void AdminWindow::on_pushButton_2_clicked()
{
    baseForm->show();
}


void AdminWindow::on_pushButton_clicked()
{
    resultForm->show();
}

