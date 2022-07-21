#ifndef FILLRESULT_H
#define FILLRESULT_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPainter>
#include <QFileDialog>
#include <QPixmap>

namespace Ui {
class FillResult;
}

class FillResult : public QWidget
{
    Q_OBJECT

public:
    explicit FillResult(QVariantList result,QMap<QString, int> themes, QWidget *parent = nullptr);
    ~FillResult();

    void setTable(QMap<QString,int> resultMap);

public slots:
    void printScr();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FillResult *ui;
    QVariantList take_data;

};

#endif // FILLRESULT_H
