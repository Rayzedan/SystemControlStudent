#ifndef FILLRESULT_H
#define FILLRESULT_H

#include <QWidget>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPainter>
#include "adminwin.h"
#include <QFileDialog>
#include <QPixmap>

namespace Ui {
class FillResult;
}

class FillResult : public QWidget
{
    Q_OBJECT

public:
    explicit FillResult(QWidget *parent = nullptr);
    ~FillResult();

    void setTable(QMap<QString,int> resultMap, QMap<QString, int> allAnswers);    

public slots:
    void takeData(QMap<QString, int> countAllAnswers, QVariantList result, QMap<QString, int> themes);
    void takePath();

signals:
    void startWindow();

private slots:
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::FillResult *ui;
    QMap<QString, int> allAnswers;
    QVariantList take_data;
    QString resultThemes;
    QString newPath;
    QString pathToPdf;
    QString html;

};

#endif // FILLRESULT_H
