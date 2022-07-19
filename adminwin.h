#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <QCloseEvent>
#include "tabwidget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "fillresult.h"

namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWin(QWidget *parent = nullptr);
    ~AdminWin();

signals:
    void secondWindow(); //Сигнал для соединения панели администратора и начального окна
    void sendData(QString str);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_comboBox_5_currentTextChanged(const QString &arg1);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

private:
    Ui::AdminWin *ui;
    QSqlQueryModel *model_res;
    FillResult *RezWin;
    FillResult *Rezform;
};

#endif // ADMINWIN_H
