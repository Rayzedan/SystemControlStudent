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
    else if (dataUser[0].toString()=="департамент" && data[2].toString() =="UPDATE")
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
        ui->label_4->hide();
        ui->comboBox->hide();
        mode = 2;

    } else if (data[0].toString()=="курс" && dataUser[2].toString() == "UPDATE"){
        QSqlQuery query;
        model1 = new QSqlQueryModel();
        query.exec("SELECT Id,Description From Courses WHERE Name = '"+data[1].toString()+"';");
        query.next();        
        QString id = query.value("Id").toString();
        QString desc = query.value("Description").toString();
        qDebug() << id;
        query.clear();
        query.exec("SELECT Time From TimeCourses WHERE CourseId = "+id+";");
        query.next();        
        QString time = query.value("Time").toString();
        query.clear();
        model1->setQuery("SELECT Name From Departments");
        ui->label_1->setText("Имя курса");
        ui->label_2->setText("Описание курса");
        ui->label_3->setText("Время");
        ui->label_4->setText("Выбранный департамент");
        ui->lineEdit->setText(data[1].toString());
        ui->lineEdit_2->setText(desc);
        ui->lineEdit_3->setText(time);        
        ui->comboBox->setModel(model1);
        ui->comboBox->setCurrentIndex(data[4].toInt());
        ui->comboBox->setCurrentText(data[3].toString());
        mode = 2;
    }
    if (data[0].toString()=="тема" && data[2].toString() =="INSERT"){
        ui->label_1->setText("Название темы");
        ui->label_2->setText("Номер темы");
        ui->label_3->setText("Количество вопросов");
        ui->label_4->hide();
        ui->comboBox->hide();
        mode = 3;
    } else if ((data[0].toString()=="тема" && data[2].toString() == "UPDATE")) {
        QSqlQuery query;
        query.exec("SELECT Id, Number From Chapters WHERE Name = '"+data[1].toString()+"';");
        query.next();
        QString id = query.value("Id").toString();
        QString number = query.value("Number").toString();
        query.clear();
        query.exec("SELECT Count From CountChapters WHERE ChapterId = "+id+";");
        query.next();
        QString count = query.value("Count").toString();
        query.clear();        
        ui->label_1->setText("Название темы");
        ui->label_2->setText("Номер темы");
        ui->label_3->setText("Количество вопросов");
        ui->label_4->setText("Выбранный курс");
        ui->lineEdit->setText(data[1].toString());
        ui->lineEdit_2->setText(number);
        ui->lineEdit_3->setText(count);
        ui->comboBox->addItem(data[3].toString(),QVariant(0));
        ui->comboBox->setCurrentIndex(0);
        mode = 3;
    };

    if (data[0].toString()=="Вопрос" && data[2].toString() =="INSERT"){
        ui->label_1->setText("Формулировка вопроса");
        ui->label_2->setText("Варианты ответов");
        ui->label_3->setText("Корректный ответ");
        ui->label_4->setText("Тип вопроса");
        ui->comboBox->addItem("Тестовый вопрос");
        ui->comboBox->addItem("Развернутый вопрос");
        ui->comboBox->setCurrentIndex(0);
        mode = 4;
    } else if ((data[0].toString()=="Вопрос" && data[2].toString() == "UPDATE")) {
        QSqlQuery query;
        query.exec("SELECT Id, Variant1, Variant2, Variant3, Variant4, CorrectAnswer From Questions WHERE question = '"+data[1].toString()+"';");
        query.next();
        QString id = query.value("Id").toString();
        QString variants= query.value("Variant1").toString()+"; "+query.value("Variant2").toString()+"; "+query.value("Variant3").toString()\
                +"; "+query.value("Variant4").toString();
        QString answer=query.value("CorrectAnswer").toString();
        ui->label_1->setText("Формулировка вопроса");
        ui->label_2->setText("Варианты ответов");
        ui->label_3->setText("Корректный ответ");
        ui->label_4->setText("Выбранная тема");
        ui->lineEdit->setText(data[1].toString());
        ui->lineEdit_2->setText(variants);
        ui->lineEdit_3->setText(answer);
        ui->comboBox->addItem(data[3].toString(),QVariant(0));
        ui->comboBox->setCurrentIndex(0);
        mode = 4;
    };
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
        db->createCourse(ui->lineEdit->text(), ui->lineEdit_2->text(),data[3].toString());
        db->createCourseTime(ui->lineEdit_3->text(),ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 2 && data[2].toString() == "UPDATE")
    {
        db->updateCourse(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(),ui->comboBox->currentText());
        db->updateCourseTime(ui->lineEdit_3->text(),ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 3 && data[2].toString() == "INSERT")
    {
        db->createChapter(ui->lineEdit->text(), ui->lineEdit_2->text(),data[3].toString());
        db->createChapterCount(ui->lineEdit_3->text(),ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 3 && data[2].toString() == "UPDATE")
    {
        db->updateChapter(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(),ui->comboBox->currentText());
        db->updateChapterCount(ui->lineEdit_3->text(),ui->lineEdit->text());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 4 && data[2].toString() == "INSERT")
    {
        db->createQuestion(ui->comboBox->currentText(),ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),data[3].toString());
        emit updateBase(mode);
        this->close();
    }
    if (mode == 4 && data[2].toString() == "UPDATE")
    {
        db->updateQuestion(data[1].toString(),ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),ui->comboBox->currentText());
        emit updateBase(mode);
        this->close();
    }
}

