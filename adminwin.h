#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <QCloseEvent>
#include "tabwidget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "QSettings"
#include "database.h"
#include "addusers.h"
#include "chaptersettings.h"
#include "settingsquestion.h"

namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
     explicit AdminWin(QWidget *parent = nullptr);
    ~AdminWin();
    QString pathFile;

    void CourseQuery(QString arg);
    void ChapterQuery(QString arg);

public slots:
    void startUpdateBase(int mode);
    void takeLogin(QString login);

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

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_comboBox_5_currentTextChanged(const QString &arg1);

    void on_comboBox_6_currentTextChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
private:
    Ui::AdminWin *ui;
    DataBase *db;
    QVariant val;
    QVariantList data;
    int indexTab;
    QVariant valTheme;
    QVariant valCourse;
    QVariant valDepart;
    QVariant valQuestion;
    QSqlQueryModel *model_res;
    QSqlQueryModel *model_res_users;
    QSqlQueryModel *model_res_depart;
    QSqlQueryModel *model_res_course;
    QSqlQueryModel *model_res_chapter;
    QSqlQueryModel *model_res_question;
    QSqlQuery *query;        
    AddUsers *AddWindow;
    chaptersettings *chapterWindow;
    SettingsQuestion *questionWindow;
};

#endif // ADMINWIN_H

