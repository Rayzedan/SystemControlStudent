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
    // Отображаем результаты всех студентов в форме таблицы
    model_res = new QSqlQueryModel();
    model_res->setQuery("Select StudentName AS Студент, Company AS Компания, Credit AS Результат, CorrectPercent AS Процент_правильных_ответов from Results");
    ui->tableView_2->setModel(model_res);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model_res_users = new QSqlQueryModel();
    model_res_users ->setQuery("Select login from Users");
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
        query->exec("Select Permissions from Users where Login = '" +login+ "'");
        query->next();
        QString acc =query->value("Permissions").toString();
        int accses = acc.toInt();
        for (int count = 6;count>=0;count--) {
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

void AdminWin::on_pushButton_17_clicked()
{
  db->createUser("root", "password");
}


void AdminWin::on_pushButton_7_clicked()
{
    AddWindow->show();
}

