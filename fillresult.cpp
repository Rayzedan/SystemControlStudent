#include "fillresult.h"
#include "ui_fillresult.h"
#include "studentwindow.h"

FillResult::FillResult (QVariantList result, QMap<QString, int> themes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FillResult)
{
    ui->setupUi(this);
    take_data = result;
    setTable(themes);
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

FillResult::~FillResult()
{
    delete ui;
}

void FillResult::on_pushButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileName(0,"Open File",QString(),"PNG File(*.png)");
    printScr();
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);
    if(dlg->exec() == QDialog::Accepted) {
        QImage img("print.png");
        QPainter painter(&printer);
//        QRect rect = painter.viewport();
//        QSize size = img.size();
//        size.scale(rect.size(), Qt::KeepAspectRatio);
//        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
//        painter.scale(1,1);
        painter.setWindow(img.rect());
        painter.drawImage(0,0,img,0,0,-1,-1);
        painter.end();
    }

    delete dlg;
}

void FillResult::setTable(QMap<QString, int> resultMap)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    //ui->tableWidget->setColumnHidden(1,true);
    QMap<QString, int>::const_iterator i = resultMap.constBegin();
    while (i != resultMap.constEnd())
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText(i.key());
        qDebug() << i.key();
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);
        newItem = new QTableWidgetItem();
        int item = i.value()/take_data[9].toDouble() * 100.0;
        qDebug() << item;
        newItem->setText(QString::number(item) + "%");
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);
        ++i;
    }
}

void FillResult::printScr()
{
   ui->onprint->grab().save("print.png");
}
