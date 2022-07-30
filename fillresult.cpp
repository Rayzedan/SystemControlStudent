#include "fillresult.h"
#include "ui_fillresult.h"
#include "studentwindow.h"
#include <QSettings>
#include <QDir>

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
    QPrinter printer;
    QPrintDialog* pPrintDialog = new QPrintDialog(&printer);
    QTextDocument document;
    document.setHtml(html);
    //printer.setOutputFormat(QPrinter::PdfFormat);
    if (pPrintDialog->exec() == QDialog::Accepted) {
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        document.print(&printer);
    }
    delete pPrintDialog;
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
    QString course = ui->course->text();
    QString name = ui->name->text();
    QString company = ui->company->text();
    QString time = ui->time->text();
    QString resultAll = ui->result->text();
    QString credit = ui->credit->text();
    QString current_time =ui->label_14->text();
    html =
    "<html>""<head>""<style>p,h2 {font-family: Times New Roman;font-size:14pt}</style></head>"\
    "<body><h2><center>Приложение к сертификату</center></h2>""<div><p>Выдан: "+name+\
    ", компания: '"+company+"'<br></p><p>За прохождение курса '"+course+"'<br></span></p><p>Дата прохождения:"+current_time+\
    "<br></p><p>Результаты по темам:<br>"+resultThemes+"</p><p>Общий процент верных ответов: "+credit+"<br></p><p>Время выполнения: "+time+\
    "<br></p><p>Результат: "+resultAll+"<br></p></div></body></html>";

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    if (pathToPdf !="DEFAULT") {
        QDir dir(pathToPdf + "/" +take_data[3].toString());
        if (!dir.exists()) {
            dir.mkpath(pathToPdf + "/" +take_data[3].toString());
            pathToPdf= pathToPdf + "/" + take_data[3].toString() + "/";
            qDebug() << "didnt exist path " << pathToPdf;
        }
        else {
            pathToPdf= pathToPdf + "/" + take_data[3].toString() + "/";
            qDebug() << "exist path " << pathToPdf;
        }
        printer.setOutputFileName(pathToPdf+current_time+"_"+name+".pdf");
    }
    else {
        QDir dir(QDir::currentPath() + "/" + take_data[3].toString());
        if (!dir.exists()) {
            dir.mkpath(QDir::currentPath() + "/" +take_data[3].toString());
            pathToPdf= QDir::currentPath() + "/" + take_data[3].toString() + "/";
            qDebug() << "didnt exist path " << pathToPdf;
        }
        else {
            pathToPdf= QDir::currentPath() + "/" + take_data[3].toString() + "/";
            qDebug() << "exist path " << pathToPdf;
        }
        printer.setOutputFileName(pathToPdf+current_time+"_"+name+".pdf");
    }
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));
    document.print(&printer);
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
