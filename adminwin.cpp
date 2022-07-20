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

    model_res_users = new QSqlQueryModel();
    model_res = new QSqlQueryModel();

    model_res->setQuery("Select StudentName AS Студент, Company AS Компания, Credit AS Результат, CorrectPercent AS Процент_правильных_ответов from Results");
    model_res_users ->setQuery("Select login from Users");
    ui->tableView_2->setModel(model_res);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->usersView->setModel(model_res_users);

    ui->usersView->setStyleSheet( "QListView::item { border-bottom: 1px solid black; }" );

    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);
    ui->tabWidget->setTabEnabled(6,false);
    ui->tabWidget->setTabEnabled(7,false);

    query = new QSqlQuery();
    //нужно вбить в Login логин текущего пользователя
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
                ui->tableView_2->setModel(model_res);
                ui->tableView_2->verticalHeader()->setVisible(false);
                ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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


//void AdminWin::setTableUsers(int value)
//{

//}

//void AdminWin::on_tabWidget_tabBarDoubleClicked(int index)
//{
//    if (accses >=128)
//    {
    // Отображаем результаты всех студентов в форме таблицы
//    model_res = new QSqlQueryModel();
//    model_res->setQuery("Select StudentName AS Студент, Company AS Компания, Credit AS Результат, CorrectPercent AS Процент_правильных_ответов from Results");
//    ui->tableView_2->setModel(model_res);
//    ui->tableView_2->verticalHeader()->setVisible(false);
//   ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    }
//}


void AdminWin::on_pushButton_7_clicked()
{
    AddWindow->show();
}



