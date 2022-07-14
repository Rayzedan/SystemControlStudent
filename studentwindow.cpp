#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "authorizationwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
    testWindow = new TestForStudent();
=======

    // Выделяем память под данные из бд для ComboBox_2/ComboBox_3
    model = new QSqlQueryModel();
    model_dep = new QSqlQueryModel();

    // Отправляем запрос на получение данных
    model->setQuery("Select Name From Departments");
    model_dep->setQuery("Select Name From Courses");

    // Отображаем полученные данные
    ui->comboBox_2->setModel(model);
    ui->comboBox_3->setModel(model_dep);
>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)

}


StudentWindow::~StudentWindow()
{
    delete ui;
}

// Кнопка возврата к начальному окну
void StudentWindow::on_pushButton_3_clicked()
{
    //ui->comboBox_2->clear();
    //ui->comboBox_3->clear();
    this->destroy();
    emit firstWindow();
}


void StudentWindow::on_pushButton_clicked()
{
<<<<<<< HEAD
    testWindow->show();
    this->destroy();
=======
    QString fullName = ui->fullName->text();
    QString company = ui->company->text();
>>>>>>> 276a248 (добавил парсинг данных из бд в окно студента)

}

