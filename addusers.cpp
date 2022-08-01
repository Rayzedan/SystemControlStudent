#include "addusers.h"
#include "ui_addusers.h"

AddUsers::AddUsers(QVariant dataUser,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUsers)
{
    ui->setupUi(this);
    if (dataUser!=-1){
        model = new QSqlQuery();
        ui->label->setText("Изменение администратора");
        ui->lineEdit->setText(dataUser.toString());
        model->exec("Select Login, Password, Permissions From Users  Where Login='"+dataUser.toString()+"';");
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        model->next();
        ui->lineEdit_2->setText(model->value("Password").toString());

        int chPrem =model->value("Permissions").toInt();
        qDebug()<<chPrem;
        for (int count=6;count>=2;count--){
            int check =pow(2,count);
            if (chPrem-check>=0){
                chPrem=chPrem-check;
                qDebug()<<"Текущее значение"<<chPrem;
                switch (check) {
                case 4:
                   ui->departbox->setChecked(true);
                   qDebug()<<1;
                    break;
                case 8:
                    ui->coursebox->setChecked(true);
                    qDebug()<<2;
                    break;
                case 16:
                    ui->chapterbox->setChecked(true);
                    qDebug()<<3;
                    break;
                case 32:
                    ui->basebox->setChecked(true);
                    qDebug()<<4;
                    break;
                case 64:
                    ui->rezbox->setChecked(true);
                    qDebug()<<5;
                    break;
                }
            }
        }

        query = new QSqlQuery();
        query->prepare("UPDATE Users set Login=:login, Password=:password, Permissions=:perm Where Login='"+dataUser.toString()+"';");
        emit updateUsers(0);
    }
}

AddUsers::~AddUsers()
{
    delete ui;
    delete db;
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
    Newpassword = db->encryptPassword(ui->lineEdit_2->text());

    if (ui->label->text()=="Изменение администратора"){
        query->bindValue(":login",Newlogin);
        query->bindValue(":password",Newpassword);
        query->bindValue(":perm",NewPerm);
        qDebug()<<NewPerm<<query->lastQuery();
        query->exec();

    } else{
        QSqlQuery setquery;
        setquery.exec("Insert into Users(Login,Password,Permissions) Values ('" +Newlogin+ "','" +Newpassword+ "'," +NewPerm+ ")");
    }
    emit updateUsers(0);
    this->close();
}

