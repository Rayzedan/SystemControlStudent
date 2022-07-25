#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <QCloseEvent>
#include "tabwidget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "database.h"
#include "addusers.h"
#include "addvariants.h"
#include "chaptersettings.h"

namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWin(QVariantList dataUser,QWidget *parent = nullptr);
    ~AdminWin();
    QString pathFile;

public slots:
    void startUpdateBase(int mode);

signals:
    void secondWindow(); //Сигнал для соединения панели администратора и начального окна
    void takePath(QString);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_usersView_clicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_pushButton_10_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_19_clicked();

    void on_DepartView_clicked(const QModelIndex &index);

    void on_pushButton_12_clicked();

    void on_courseView_clicked(const QModelIndex &index);

    void on_pushButton_17_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_20_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_21_clicked();

    void on_toolButton_clicked();

private:
    Ui::AdminWin *ui;
    DataBase *db;
    QVariant val;
    QVariantList data;    
    QSqlQueryModel *model_res;
    QSqlQueryModel *model_res_users;
    QSqlQueryModel *model_res_depart;
    QSqlQueryModel *model_res_course;
    QSqlQueryModel *model_res_chapter;
    QSqlQuery *query;
    AddUsers *AddWindow;
    chaptersettings *chapterWindow;
    AddVariants *varWind;
};

#endif // ADMINWIN_H

