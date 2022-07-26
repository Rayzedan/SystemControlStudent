#include "chaptersettings.h"
#include "ui_chaptersettings.h"

chaptersettings::chaptersettings(QVariantList dataUser, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chaptersettings)
{
    ui->setupUi(this);
    query = new QSqlQuery();
    model = new QSqlQueryModel();
    data = dataUser;
    qDebug()<<dataUser;
    setData(data);

}

chaptersettings::~chaptersettings()
{
    delete ui;
    delete query;
    delete model;
    delete db;
}

void chaptersettings::setData(QVariantList dataUser)
{
    if (dataUser[0].toString()=="департамент" && dataUser[2].toString() == "INSERT") {
       ui->label_2->hide();
       ui->label_3->hide();
       ui->label_4->hide();
       ui->comboBox->hide();
       ui->lineEdit_2->hide();
       ui->lineEdit_3->hide();
       mode = 1;
       ui->label_1->setText("Имя департамента");
    }
    else if (data[2].toString() =="UPDATE")
    {
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->comboBox->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        mode = 1;
        ui->label_1->setText("Имя департамента");
        ui->lineEdit->setText(data[1].toString());
    }
    if (data[0].toString()=="курс" && dataUser[2].toString() == "INSERT") {
        ui->label_1->setText("Имя курса");
        ui->label_2->setText("Описание курса");
        ui->label_3->setText("Время");
        ui->label_4->setText("Выбранный департамент");
        ui->comboBox->addItem(data[3].toString(),QVariant(0));
        ui->comboBox->setCurrentIndex(0);
        mode = 2;
    }
//    if (data[0].toString()=="тема"){
//        model->setQuery("Select Name From Courses order by Name");
//        ui->comboBox->setModel(model);
//        ui->label_8->setText("раздела");
//        ui->label_6->setText("новый номер раздела");
//        ui->label_10->setText("курс для нового раздела");
//        mode = 3;
//    }
}

void chaptersettings::on_pushButton_2_clicked()
{
    if (mode == 1 && data[2].toString() =="UPDATE")
    {
        db->updateDepart(data[1].toString(), ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode ==1 && data[2].toString() =="INSERT")
    {
        db->createDepart(ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 2 && data[2].toString() == "INSERT")
    {
//        db->updateCourse(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(),ui->comboBox->currentText());
//        emit updateBase(mode);
        this->close();
    }
    if (mode == 1 && data[2].toString() == "UPDATE")
    {
        db->updateCourse(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(),ui->comboBox->currentText());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 3)
    {
        db->updateChapter(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(),ui->comboBox->currentText());
        emit updateBase(mode);
        this->close();
    }
}

