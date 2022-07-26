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
    explicit FillResult(QMap<QString, int> countAllAnswers, QVariantList result, QMap<QString, int> themes, QWidget *parent = nullptr);
    ~FillResult();

    void setTable(QMap<QString,int> resultMap, QMap<QString, int> allAnswers);    

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

};

#endif // FILLRESULT_H
