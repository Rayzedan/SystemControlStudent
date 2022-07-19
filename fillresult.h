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
    explicit FillResult(QWidget *parent = nullptr);
    ~FillResult();

signals:
    void fullrez();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FillResult *ui;
    QSqlQuery *query;
};

#endif // FILLRESULT_H
