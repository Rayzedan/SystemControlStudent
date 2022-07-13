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
    ui->setupUi(this);
    ui->pushButton_4->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_toolButton_clicked() //Кнопка для создания задания
{
    questForm->show();
}


void AdminWindow::on_toolButton_3_clicked() //Кнопка для создания департамента
{
    departForm->show();
}


void AdminWindow::on_toolButton_4_clicked() //Кнопка для создания курса
{
   courseForm->show();
}


void AdminWindow::on_ButDeppart_clicked() //Кнопка для создания темы
{
   topicForm->show();
}


void AdminWindow::on_pushButton_4_clicked() //Кнопка возврата в окно авторизации
{
    this->close();
    emit backToAuth();
}

