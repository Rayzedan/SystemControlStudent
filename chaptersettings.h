#ifndef CHAPTERSETTINGS_H
#define CHAPTERSETTINGS_H

#include <QDialog>
#include "database.h"

namespace Ui {
class chaptersettings;
}

class chaptersettings : public QDialog
{
    Q_OBJECT

public:
    explicit chaptersettings(QVariantList dataUser, QWidget *parent = nullptr);
    ~chaptersettings();
    void setData(QVariantList dataUser);

signals:
    updateBase(int mode);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::chaptersettings *ui;
    QSqlQueryModel *model;
    QSqlQuery *query;
    DataBase *db;
    QVariantList data;
    int mode;
};

#endif // CHAPTERSETTINGS_H
