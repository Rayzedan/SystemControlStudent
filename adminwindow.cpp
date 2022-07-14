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

    // Связываем окно редактирования вопроса и окно администратора
    connect(questForm, &questionedit::backToAdm, this, &AdminWindow::show);

    // Связываем окно редактирования департамента и окно администратора
    connect(departForm, &departedit::backToAdm, this, &AdminWindow::show);

    // Связываем окно редактирования курса и окно администратора
    connect(courseForm, &courseedit::backToAdm, this, &AdminWindow::show);

    // Связываем окно редактирования темы и окно администратора
    connect(topicForm, &topicedit::backToAdm, this, &AdminWindow::show);

    // Связываем окно редактирования бд и окно администратора
    connect(baseForm, &BaseWindow::backToAdm, this, &AdminWindow::show);

    // Связываем окно просмотра результата и окно администратора
    connect(resultForm, &ResultsWindow::backToAdm, this, &AdminWindow::show);

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
    this->close();
    questForm->show();
}

// Кнопка для создания департамента
void AdminWindow::on_toolButton_3_clicked()
{
    this->close();
    departForm->show();
}

// Кнопка для создания курса
void AdminWindow::on_toolButton_4_clicked()
{
   this->close();
   courseForm->show();
}

// Кнопка для открытия бд
void AdminWindow::on_pushButton_2_clicked()
{
    this->close();
    baseForm->show();
}

// Кнопка для открытия результатов
void AdminWindow::on_pushButton_clicked()
{
    this->close();
    resultForm->show();
}

// Кнопка для создания темы
void AdminWindow::on_ButDeppart_clicked()
{
   this->close();
   topicForm->show();
}

// Кнопка возврата в окно авторизации
void AdminWindow::on_pushButton_4_clicked()
{
    this->destroy();
    emit backToAuth();
}
