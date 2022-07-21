#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class usersettings;
}

class usersettings : public QDialog
{
    Q_OBJECT

public:
    explicit usersettings(QVariant dataUser,QWidget *parent = nullptr);
    ~usersettings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::usersettings *ui;
    QSqlQuery *query;
};

#endif // USERSETTINGS_H
