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

    if (dataUser[0].toString()=="департамент") {
       ui->label_5->hide();
       ui->label_6->hide();
       ui->label_9->hide();
       ui->label_10->hide();
       ui->comboBox->hide();
       ui->lineEdit_2->hide();
       mode = 1;
       ui->label_8->setText("департамента");      
    }
    else if (data[0].toString()=="курс"){
        model->setQuery("Select Name From Departments order by Name");
        ui->comboBox->setModel(model);
        ui->label_8->setText("курса");
        ui->label_6->setText("новое описание для курса");
        ui->label_10->setText("департамент для нового курса");
        mode = 2;        
    } else if (data[0].toString()=="тема"){
        model->setQuery("Select Name From Courses order by Name");
        ui->comboBox->setModel(model);
        ui->label_8->setText("раздела");
        ui->label_6->setText("новый номер раздела");
        ui->label_10->setText("курс для нового раздела");
        mode = 3;        
    }
}

chaptersettings::~chaptersettings()
{
    delete ui;
    delete query;
    delete model;
    delete db;
}

void chaptersettings::on_pushButton_2_clicked()
{
    if (mode == 1)
    {
        db->updateDepart(data[1].toString(), ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 2)
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

