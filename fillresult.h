#ifndef FILLRESULT_H
#define FILLRESULT_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>

namespace Ui {
class FillResult;
}

class FillResult : public QWidget
{
    Q_OBJECT

public:
    explicit FillResult(QVariantList result, QWidget *parent = nullptr);
    ~FillResult();


private slots:
    void on_pushButton_clicked();

private:
    Ui::FillResult *ui;
    QVariantList take_data;

};

#endif // FILLRESULT_H
