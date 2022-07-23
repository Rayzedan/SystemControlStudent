#ifndef ADDUSERS_H
#define ADDUSERS_H

#include <QDialog>
#include <QSqlQuery>
#include "database.h"

namespace Ui {
class AddUsers;
}

class AddUsers : public QDialog
{
    Q_OBJECT

public:
    explicit AddUsers(QWidget *parent = nullptr);
    ~AddUsers();

    QString encryptPas(const QString pass) {
        DataBase base;
        QString cryptedpas = base.encryptPassword(pass);
        return cryptedpas;
    };


private slots:
    void on_pushButton_clicked();

private:
    Ui::AddUsers *ui;
    DataBase *db;
};

#endif // ADDUSERS_H
