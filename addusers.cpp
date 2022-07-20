#include "addusers.h"
#include "ui_addusers.h"

AddUsers::AddUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUsers)
{
    ui->setupUi(this);  
}

AddUsers::~AddUsers()
{
    delete ui;
}

void AddUsers::on_pushButton_clicked()
{
    QString Newlogin = ui->lineEdit->text();
    QString Newpassword = ui->lineEdit_2->text();

    int NewPermision =0;
    if (ui->departbox->isChecked()) {
        NewPermision+=4;
    };
    if (ui->coursebox->isChecked()) {
        NewPermision+=8;
    };
    if (ui->chapterbox->isChecked()) {
        NewPermision+=16;
    };
    if (ui->basebox->isChecked()) {
        NewPermision+=32;
    };
    if (ui->rezbox->isChecked()) {
        NewPermision+=64;
    };
    QString NewPerm =QString::number(NewPermision);
    QSqlQuery query;
    qDebug() << Newlogin << Newpassword<<NewPermision;
    query.exec("Insert into Users(Login,Password,Permissions) Values ('" +Newlogin+ "','" +Newpassword+ "'," +NewPerm+ ")");
    this->close();
}

