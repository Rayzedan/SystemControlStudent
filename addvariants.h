#ifndef ADDVARIANTS_H
#define ADDVARIANTS_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "database.h"
namespace Ui {
class AddVariants;
}

class AddVariants : public QDialog
{
    Q_OBJECT

public:
    explicit AddVariants(QVariantList data, QWidget *parent = nullptr);
    ~AddVariants();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddVariants *ui;
    QSqlQuery *query;
    QSqlQuery *helpQ;
};

#endif // ADDVARIANTS_H
