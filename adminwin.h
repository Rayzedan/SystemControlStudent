#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <QCloseEvent>
#include "tabwidget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "fillresult.h"
#include "database.h"
#include "addusers.h"
namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWin(QVariantList dataUser,QWidget *parent = nullptr);
    ~AdminWin();

signals:
    void secondWindow(); //Сигнал для соединения панели администратора и начального окна

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_comboBox_5_currentTextChanged(const QString &arg1);


    void on_pushButton_7_clicked();

private:
    Ui::AdminWin *ui;
    DataBase *db;
    QVariantList data;
    QSqlQueryModel *model_res;
    QSqlQueryModel *model_res_users;
    QSqlQuery *query;
    AddUsers *AddWindow;
};

#endif // ADMINWIN_H

