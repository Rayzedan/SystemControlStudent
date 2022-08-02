#include "settingsquestion.h"
#include "ui_settingsquestion.h"

SettingsQuestion::SettingsQuestion(QVariantList date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsQuestion)
{
    ui->setupUi(this);
    data = date;
    qDebug()<<data;
    if (data[0].toString()!="empty"){
        QSqlQuery query;
        query.exec("Select * From Questions Where Id="+data[0].toString()+";");
        query.next();
        QString question = query.value("Question").toString();
        int type = query.value("TypeQuestion").toInt();
        QString ch1 = query.value("Variant1").toString();
        QString ch2 = query.value("Variant2").toString();
        QString ch3 = query.value("Variant3").toString();
        QString ch4 = query.value("Variant4").toString();
        int ans = query.value("CorrectAnswer").toInt();

        ui->textEdit_2->setText(question);
        if (type==0){
            ui->stackedWidget->setCurrentIndex(0);
            ui->lineEdit->setText(ch1);
            ui->lineEdit_2->setText(ch2);
            ui->lineEdit_3->setText(ch3);
            ui->lineEdit_4->setText(ch4);
            for (int count=3;count>=0;count--){
                int val = pow(2,count);
                if (ans-val>=0){
                    ans-=val;
                    switch (val) {
                    case 1:
                        ui->checkBox->setChecked(1);
                        break;
                    case 2:
                        ui->checkBox_2->setChecked(1);
                        break;
                    case 4:
                        ui->checkBox_3->setChecked(1);
                        break;
                    case 8:
                        ui->checkBox_4->setChecked(1);
                        break;
                    }
                }
            }
        } else {
            ui->stackedWidget->setCurrentIndex(1);
            ui->textEdit->setText(ch1);
        }
    }
}

SettingsQuestion::~SettingsQuestion()
{
    delete ui;
}

void SettingsQuestion::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1=="Тестовый"){
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->stackedWidget->setCurrentIndex(1);
    }
}



void SettingsQuestion::on_pushButton_clicked()
{
    QString type = ui->comboBox->currentText();
    QString question = ui->textEdit_2->toPlainText();
    QString variants = ""+ui->lineEdit->text()+"; "+ui->lineEdit_2->text()+\
            "; "+ui->lineEdit_3->text()+"; "+ui->lineEdit_4->text()+"";
    int ans = 0;
    if (ui->checkBox->isChecked()){
        ans+=1;
    }
    if (ui->checkBox_2->isChecked()){
        ans+=2;
    }
    if (ui->checkBox_3->isChecked()){
        ans+=4;
    }
    if (ui->checkBox_4->isChecked()){
        ans+=8;
    }
    QString answer = QString::number(ans);
    QString chapter = data[1].toString();
    QString oldquestionid = data[0].toString();
    qDebug() <<type<<question<<variants<<answer<<chapter;
    if (data[0].toString()=="empty"){
        db->createQuestion(type,question,variants,answer,chapter);
    }else{
        db->updateQuestion(type,question,variants,answer,chapter,oldquestionid);
    }


    //this->close();
}

