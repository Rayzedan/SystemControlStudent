#include "fillresult.h"
#include "ui_fillresult.h"
#include "studentwindow.h"
#include <QSettings>

FillResult::FillResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FillResult)
{
    ui->setupUi(this);    

}

FillResult::~FillResult()
{
    delete ui;
}

void FillResult::on_pushButton_clicked()
{
    QString course = ui->course->text();
    QString name = ui->name->text();
    QString company = ui->company->text();
    QString time = ui->time->text();
    QString result = ui->result->text();
    QString credit = ui->credit->text();
    QString current_time =ui->label_14->text();
    QString html =
    "<html>""<head>""<style>p,h2 {font-family: Times New Roman;font-size:14pt}</style></head>"\
    "<body><h2><center>Результаты Тестирования</center></h2>""<div><p>Курс: "+course+"<br></span></p><p>ФИО: "+name+\
    "<br></p><p>Компания: "+company+"<br></p><p>Дата:"+current_time+"<br></p><p>Общий процент верных ответов: "+credit+\
    "<br></p><p>Результаты по темам:<br>"+resultThemes+"</p><p>Время выполнения: "+time+"<br></p><p>Результат: "+result+\
            "<br></p></div></body></html>";

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/pro/"+current_time+"_"+take_data[3].toString()+"_"+name+".pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));
    document.print(&printer);
}

void FillResult::setTable(QMap<QString, int> resultMap, QMap<QString, int> allAnswers)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->setColumnHidden(1,true);
    QMap<QString, int>::const_iterator i = resultMap.constBegin();
    while (i != resultMap.constEnd())
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText(i.key());
        resultThemes+=i.key()+" ";        
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);
        newItem = new QTableWidgetItem();        
        double item = static_cast<double>(i.value()) / allAnswers[i.key()] * 100.0;
        resultThemes+= QString::number(item) + "%" + "<br>";
        qDebug() << item;
        newItem->setText(QString::number(item,'f',0) + "%");
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);
        ++i;
    }
}

void FillResult::takeData(QMap<QString, int> countAllAnswers, QVariantList result, QMap<QString, int> themes)
{
    takePath();
    take_data = result;
    setTable(themes, countAllAnswers);
    ui->name->setText(take_data[0].toString());
    ui->company->setText(take_data[1].toString());
    ui->label_14->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy г"));
    ui->credit->setText(take_data[4].toString() + "%");
    if (take_data[5].toInt()==1)
    {
      ui->result->setText("Зачёт");
    }
    else
    {
      ui->result->setText("Незачёт");
    }
    ui->course->setText(take_data[7].toString());
    ui->time->setText(take_data[8].toString());
}

void FillResult::takePath()
{
    QString fileName = "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup("userSettings");
    pathToPdf.append(settings.value("path").toString());
    settings.endGroup();
    qDebug() << pathToPdf;

}

// Закрываем окно
void FillResult::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit startWindow();

}
