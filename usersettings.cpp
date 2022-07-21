#include "usersettings.h"
#include "ui_usersettings.h"

usersettings::usersettings(QVariant dataUser,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usersettings)
{

    ui->setupUi(this);
    ui->label_2->setText(dataUser.toString());
    query = new QSqlQuery();
    query->prepare("UPDATE Users set Permissions=:perm WHERE Login='"+dataUser.toString()+"';");
}
usersettings::~usersettings()
{
    delete ui;
}

void usersettings::on_pushButton_clicked()
{
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
    }
    QString NewPerm =QString::number(NewPermision);
    query->bindValue(":perm",NewPerm);
    query->exec();
    this->close();
}

