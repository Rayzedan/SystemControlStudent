#include "studentwindow.h"
#include "ui_studentwindow.h"



StudentWindow::StudentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);

    // Выделяем память под данные из бд для ComboBox_2/ComboBox_3
    model = new QSqlQueryModel();
    model_dep = new QSqlQueryModel();

    // Отправляем запрос на получение данных
    model->setQuery("Select Name From Departments");
    model_dep->setQuery("Select Name From Courses");

    // Отображаем полученные данные
    ui->comboBox_2->setModel(model);
    ui->comboBox_3->setModel(model_dep);



}


StudentWindow::~StudentWindow()
{
    delete ui;
}

// Кнопка возврата к начальному окну
void StudentWindow::on_pushButton_3_clicked()
{
    this->close();
    emit firstWindow();
}

// Кнопка для открытия теста
void StudentWindow::on_pushButton_clicked()
{
    // Отправляем данные, которые ввёл пользователь в окно с тестом
    QVariantList data;
    data.append(ui->fullName->text());
    data.append(ui->company->text());
    data.append(ui->comboBox_2->currentText());
    data.append(ui->comboBox_3->currentText());
    this->close();
    qDebug() << data;
    testWindow = new TestForStudent(data, this);
    testWindow->show();
}
