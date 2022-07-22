#include "adminwin.h"
#include "ui_adminwin.h"

AdminWin::AdminWin(QVariantList dataUser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWin)
{
    ui->setupUi(this);
    AddWindow = new AddUsers();
    data = dataUser;
    QString login = data[0].toString();

    model_res = new QSqlQueryModel();
    model_res->setQuery("Select StudentName AS Студент, Company AS Компания, Credit AS Результат, CorrectPercent AS Процент_правильных_ответов From Results");
    ui->tableView_2->setModel(model_res);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    model_res_users = new QSqlQueryModel();
    model_res_users ->setQuery("Select login From Users Order by login");
    ui->usersView->setModel(model_res_users);
    ui->usersView->setStyleSheet( "QListView::item { border-bottom: 1px solid black; }" );


    model_res_depart = new QSqlQueryModel();
    model_res_depart->setQuery("Select name From Departments Order by name");
    ui->DepartView->setModel(model_res_depart);
    ui->DepartView->setStyleSheet( "QListView::item { border-bottom: 1px solid black; }" );


    ui->comboBox->setModel(model_res_depart);
    ui->comboBox_2->setModel(model_res_depart);

    model_res_course = new QSqlQueryModel();

    model_res_chapter = new QSqlQueryModel();


    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);
    ui->tabWidget->setTabEnabled(6,false);
    ui->tabWidget->setTabEnabled(7,false);

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
                qDebug() <<"Разрешили вопросы";
                break;
            case 2:
                ui->tabWidget->setTabEnabled(1,true);
                qDebug() <<"Разрешили настройки";
                break;
            case 4:
                ui->tabWidget->setTabEnabled(2,true);
                qDebug() <<"Разрешили пользователи";
                break;
            case 8:
                ui->tabWidget->setTabEnabled(3,true);
                qDebug() <<"Разрешили департаменты";
                break;
            case 16:
                ui->tabWidget->setTabEnabled(4,true);
                qDebug() <<"Разрешили курсы";
                break;
            case 32:
                ui->tabWidget->setTabEnabled(5,true);
                qDebug() <<"Разрешили темы";
                break;
            case 64:
                ui->tabWidget->setTabEnabled(6,true);
                qDebug() <<"Разрешили базу";
                break;
            case 128:
                ui->tabWidget->setTabEnabled(7,true);
                qDebug() <<"Разрешили результаты";
                break;
            }
        }
    }
}



AdminWin::~AdminWin()
{
    delete ui;
}

// Закрываем окно
void AdminWin::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit secondWindow();
}

void AdminWin::on_pushButton_7_clicked()
{
    AddWindow->show();
}




void AdminWin::on_usersView_clicked(const QModelIndex &index)
{
    val = index.data().toString();
}

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

void AdminWin::on_pushButton_9_clicked()
{
    if (val.toString()==""){
        QMessageBox ::critical(this, "", "Сначала выберете пользователя для настройки.");
    }else if (val.toString()=="Администратор"){
        QMessageBox ::critical(this, "", "Нельзя менять права администратора");
    } else {
        qDebug()<<val.toString();
        SettWindow = new usersettings(val.toString());
        SettWindow ->show();
    }
}


void AdminWin::on_comboBox_currentTextChanged(const QString &arg1)
{
    model_res_course = new QSqlQueryModel();
    model_res_course->setQuery("Select Courses.name from Courses, Departments where Departments.name='"+arg1+"' and Departments.Id=Courses.DepartmentId");
    ui->courseView->setModel(model_res_course);
    ui->courseView->setStyleSheet( "QListView::item { border-bottom: 1px solid black; }" );
}


void AdminWin::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    model_res_course->setQuery("Select Courses.name from Courses, Departments where Departments.name='"+arg1+"' and Departments.Id=Courses.DepartmentId");
    ui->comboBox_3->setModel(model_res_course);
}

void AdminWin::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    qDebug()<<"Open";
    model_res_chapter->setQuery("Select Chapters.name from Chapters, Courses where Courses.name='"+arg1+"' and Courses.Id=Chapters.CourseId");
    ui->listView->setModel(model_res_chapter);
    ui->listView->setStyleSheet( "QListView::item { border-bottom: 1px solid black;}" );
}


void AdminWin::on_pushButton_10_clicked()
{
    QVariantList depart;
    depart.append("департамент");
    varWind = new AddVariants(depart);
    varWind ->show();
}


void AdminWin::on_pushButton_16_clicked()
{
    QVariantList course;
    course.append("курс");
    course.append("описание курса");
    course.append(ui->comboBox->currentText());
    varWind = new AddVariants(course);
    varWind ->show();
}


void AdminWin::on_pushButton_19_clicked()
{
    QVariantList chap;
    chap.append("тему");
    chap.append("номер темы");
    chap.append(ui->comboBox_3->currentText());
    varWind = new AddVariants(chap);
    varWind ->show();
}

