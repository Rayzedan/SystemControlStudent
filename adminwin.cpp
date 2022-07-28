#include "adminwin.h"
#include "ui_adminwin.h"
#include <QFileDialog>

AdminWin::AdminWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWin)
{
    ui->setupUi(this);
    model_res = new QSqlQueryModel();
    model_res_users = new QSqlQueryModel();
    model_res_depart = new QSqlQueryModel();
    model_res_course = new QSqlQueryModel();
    model_res_chapter = new QSqlQueryModel();
    model_res_question = new QSqlQueryModel();
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);
    ui->tabWidget->setTabEnabled(6,false);
    indexTab = 0;
}



AdminWin::~AdminWin()
{
    delete ui;
    delete model_res;
    delete model_res_chapter;
    delete model_res_course;
    delete model_res_depart;
    delete model_res_users;
    delete model_res_question;
    qDebug() << "destroy adm";
}

// Закрываем окно
void AdminWin::closeEvent(QCloseEvent *event)
{    
    event->accept();
    //this->destroy();
    emit secondWindow();
}
//Кнопка создания пользователя
void AdminWin::on_pushButton_7_clicked()
{
    QString val = "-1";
    AddWindow = new AddUsers(val);
    AddWindow->show();
}

//Выбор пользователя для удаления или изменения
void AdminWin::on_usersView_clicked(const QModelIndex &index)
{
    val = index.data().toString();
}
//Кнопка удаления пользователя
void AdminWin::on_pushButton_8_clicked()
{
    if (val.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете пользователя для удаления.");
    } else if (val.toString()=="Администратор"){
        QMessageBox ::critical(this, "", "Нельзя удалить администратора");
    } else {
        QSqlQuery query;
        query.exec("DELETE FROM Users WHERE Login='"+val.toString()+"';");
        QMessageBox :: information (this, "", "Успешное удаление пользователя.");
    }
}
//Кнопка настройки пользователя
void AdminWin::on_pushButton_9_clicked()
{
    if (val.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете пользователя для настройки.");
    }else if (val.toString()=="Администратор"){
        QMessageBox ::critical(this, "", "Нельзя менять права администратора");
    } else {
        qDebug()<<val.toString();
        AddWindow = new AddUsers(val.toString());
        AddWindow->show();
    }
}

void AdminWin::CourseQuery(QString arg){
   qDebug() << "use course";
   model_res_course->setQuery("Select Courses.name from Courses, Departments where Departments.name='"+arg+"' and Departments.Id=Courses.DepartmentId");
};
void AdminWin::ChapterQuery(QString arg){
   qDebug() << "use chapter";
   model_res_chapter->setQuery("Select Chapters.name from Chapters, Courses where Courses.name='"+arg+"' and Courses.Id=Chapters.CourseId");
};

void AdminWin::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (indexTab == 3) {
        qDebug() << "comboBox_1";
        CourseQuery(arg1);
        ui->courseView->setModel(model_res_course);
    }
}


void AdminWin::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if (indexTab == 4) {
        qDebug() << "comboBox_2";
        model_res_chapter->clear();
        CourseQuery(arg1);
        ui->comboBox_3->setModel(model_res_course);
    }
}

void AdminWin::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    if (indexTab == 4){
        qDebug()<<"comboBox_3";
        ChapterQuery(arg1);
        ui->listView->setModel(model_res_chapter);
    }
}

void AdminWin::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    if (indexTab == 5) {
        qDebug() << "comboBox_4";
        CourseQuery(arg1);
        ui->comboBox_5->setModel(model_res_course);
    }
}


void AdminWin::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    if (indexTab == 5) {
        qDebug() << arg1;
        ChapterQuery(arg1);
        ui->comboBox_6 ->setModel(model_res_chapter);
    }
}


void AdminWin::on_comboBox_6_currentTextChanged(const QString &arg1)
{
    if (indexTab == 5) {
        qDebug() << "comboBox_6";
        model_res_question->setQuery("Select Question as Вопрос, Variant1 as Вариант1, Variant2 as Вариант2, Variant3 as Вариант3, Variant4 as Вариант4, "
                                     "CorrectAnswer as Ответ from Questions, Chapters where Chapters.name='"+arg1+"' and Chapters.Id=Questions.ChapterId");
        qDebug()<<model_res_question->lastError();
        ui->tableView->setModel(model_res_question);
        ui->tableView->verticalHeader()->setVisible(false);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void AdminWin::on_pushButton_10_clicked()
{
    QVariantList depart;
    depart.append("департамент");
    depart.append("empty");
    depart.append("INSERT");
    chapterWindow = new chaptersettings(depart);
    connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
    depart.clear();
    chapterWindow ->show();
}

void AdminWin::on_pushButton_11_clicked()
{
    QVariantList depart;
    if (valDepart.toString()!= "") {
        depart.append("департамент");
        depart.append(valDepart);
        depart.append("UPDATE");
        chapterWindow = new chaptersettings(depart);
        connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
        depart.clear();
        chapterWindow ->show();
    }
    else
    {
        QMessageBox::critical(this, "", "Выберете департамент");
    }

}

void AdminWin::on_pushButton_12_clicked()
{
    if (valDepart.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете департамент для удаления.");
    } else {
        QSqlQuery query;
        query.exec("DELETE FROM Departments WHERE name='"+valDepart.toString()+"';");
        QMessageBox :: information (this, "", "Успешное удаление департамента.");
        startUpdateBase(1);
        qDebug()<< query.lastError().text();
    }
}

void AdminWin::on_pushButton_16_clicked()
{
    QVariantList course;
    course.append("курс");
    course.append("empty");
    course.append("INSERT");
    course.append(ui->comboBox->currentText());
    chapterWindow = new chaptersettings(course);
    connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
    course.clear();
    chapterWindow ->show();
}


void AdminWin::on_pushButton_19_clicked()
{
    QVariantList chap;
    chap.append("тема");
    chap.append("empty");
    chap.append("INSERT");
    chap.append(ui->comboBox_3->currentText());
    chapterWindow = new chaptersettings(chap);
    connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
    chap.clear();
    chapterWindow ->show();
}


void AdminWin::on_pushButton_17_clicked()
{
    if (valCourse.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете курс для удаления.");
    } else {
        QSqlQuery query;
        query.exec("DELETE FROM Courses WHERE name='"+valCourse.toString()+"';");
        QMessageBox :: information (this, "", "Успешное удаление курса.");
        startUpdateBase(2);
        qDebug()<< query.lastError().text();
    }
}


void AdminWin::on_listView_clicked(const QModelIndex &index)
{
    valTheme = index.data().toString();
    qDebug()<<val;
}

void AdminWin::on_pushButton_20_clicked()
{
    if (valTheme.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете тему для удаления.");
    } else {
        QSqlQuery query;
        query.exec("DELETE FROM Chapters WHERE name='"+valTheme.toString()+"';");
        QMessageBox :: information (this, "", "Успешное удаление темы.");
        startUpdateBase(3);
        qDebug()<< query.lastError().text();
    }
}

void AdminWin::on_pushButton_18_clicked()
{
    QVariantList course;
    if (valCourse.toString()!="") {
        course.append("курс");
        course.append(valCourse);
        course.append("UPDATE");
        course.append(ui->comboBox->currentText());
        chapterWindow = new chaptersettings(course);
        connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
        course.clear();
        chapterWindow ->show();
    }
    else  QMessageBox::critical(this, "", "Выберете курс");
}

void AdminWin::on_pushButton_21_clicked()
{
    QVariantList chap;
    if (valTheme.toString()!="") {
        chap.append("тема");
        chap.append(valTheme);
        chap.append("UPDATE");
        chap.append(ui->comboBox_3->currentText());
        chapterWindow = new chaptersettings(chap);
        connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
        chap.clear();
        chapterWindow ->show();
    }
}

void AdminWin::on_tableView_clicked(const QModelIndex &index)
{
    val = index.row();
    valQuestion = ui->tableView->model()->data(ui->tableView->model()->index(val.toInt(),0));
    qDebug()<<valQuestion.toString();
}

void AdminWin::on_pushButton_13_clicked()
{
    QVariantList quest;
    quest.append("Вопрос");
    quest.append("empty");
    quest.append("INSERT");
    quest.append(ui->comboBox_6->currentText());
    chapterWindow = new chaptersettings(quest);
    connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
    quest.clear();
    chapterWindow ->show();
}

void AdminWin::on_pushButton_14_clicked()
{
    QVariantList quest;
    if (valQuestion.toString()!="") {
        quest.append("Вопрос");
        quest.append(valQuestion);
        quest.append("UPDATE");
        quest.append(ui->comboBox_6->currentText());
        chapterWindow = new chaptersettings(quest);
        connect(chapterWindow, &chaptersettings::updateBase, this, &AdminWin::startUpdateBase);
        quest.clear();
        chapterWindow ->show();
    }
}

void AdminWin::on_pushButton_15_clicked()
{
    if (valQuestion.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете вопрос для удаления.");
    } else {
        QSqlQuery query;
        query.exec("DELETE FROM Questions WHERE Question='"+valQuestion.toString()+"';");
        QMessageBox :: information (this, "", "Успешное удаление вопроса.");
    }
}

void AdminWin::on_DepartView_clicked(const QModelIndex &index)
{
    valDepart = index.data().toString();
    qDebug()<<valDepart;
}

void AdminWin::on_courseView_clicked(const QModelIndex &index)
{
    valCourse = index.data().toString();
    qDebug()<<valCourse;
}

void AdminWin::on_toolButton_clicked()
{
    pathFile = QFileDialog::getExistingDirectory(this, "Выбор папки", "");
    qDebug() << pathFile;
    ui->lineEdit->setText(pathFile);
}


void AdminWin::startUpdateBase(int mode)
{
    if (mode == 1)
    {
        model_res_depart = new QSqlQueryModel();
        model_res_depart->setQuery("Select name From Departments Order by name");
        ui->DepartView->setModel(model_res_depart);
    }
    if (mode == 2)
    {
        model_res_course = new QSqlQueryModel();
        model_res_course->setQuery("Select Courses.name from Courses, Departments where Departments.name='"+ui->comboBox->currentText()+"' and Departments.Id=Courses.DepartmentId");
        ui->courseView->setModel(model_res_course);

    }
    if (mode == 3)
     {
        model_res_chapter->setQuery("Select Chapters.name from Chapters, Courses where Courses.name='"+ui->comboBox_3->currentText()+"' and Courses.Id=Chapters.CourseId");
        ui->listView->setModel(model_res_chapter);
     }
}

void AdminWin::takeLogin(QString login)
{
    model_res->setQuery("Select StudentName AS Студент, Company AS Компания, Credit AS Результат, CorrectPercent AS 'Правильных ответов' From Results");
    ui->tableView_2->setModel(model_res);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model_res_users ->setQuery("Select login From Users Order by login");
    ui->usersView->setModel(model_res_users);
    model_res_depart->setQuery("Select name From Departments Order by name");
    ui->DepartView->setModel(model_res_depart);
    ui->comboBox->setModel(model_res_depart);
    ui->comboBox_2->setModel(model_res_depart);
    ui->comboBox_4->setModel(model_res_depart);

    qDebug() << login;
    query = new QSqlQuery();
    query->exec("Select Permissions from Users where Login = '" +login+ "'");
    query->next();
    QString acc =query->value("Permissions").toString();
       int accses = acc.toInt();
    for (int count = 7;count>=0;count--)
    {
        int check =pow(2,count);
        if ((accses-check)>=0){
            accses=accses-check;
            switch (check) {
            case 1:
                ui->tabWidget->setTabEnabled(0,true);
                break;
            case 2:
                ui->tabWidget->setTabEnabled(1,true);
                break;
            case 4:
                ui->tabWidget->setTabEnabled(2,true);
                break;
            case 8:
                ui->tabWidget->setTabEnabled(3,true);
                break;
            case 16:
                ui->tabWidget->setTabEnabled(4,true);
                break;
            case 32:
                ui->tabWidget->setTabEnabled(5,true);
                break;
            case 64:
                ui->tabWidget->setTabEnabled(6,true);
                break;
            }
        }
    }
}




//Заготовка под нормальное расписывание кода по вкладкам
void AdminWin::on_tabWidget_currentChanged(int index)
{
    if (index==0){
        qDebug()<<"Вкладка Настройки";
        indexTab = 0;
    } else if (index==1) {
        qDebug()<<"Вкладка Пользователи";
        indexTab = 1;
    } else if (index==2) {
        qDebug()<<"Вкладка Департамент";
        indexTab =2;
    } else if (index==3) {
        qDebug()<<"Вкладка Курсы";
        indexTab =3;
    } else if (index==4) {
        qDebug()<<"Вкладка Темы";
        indexTab = 4;
    } else if (index==5) {
        qDebug()<<"Вкладка Вопросы";
        indexTab = 5;
    } else if (index==6) {
        qDebug()<<"Вкладка Результаты";
        indexTab = 6;
    }
}
