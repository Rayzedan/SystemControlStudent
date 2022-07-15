#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <tabwidget.h>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWin(QWidget *parent = nullptr);
    ~AdminWin();

private slots:
    void on_comboBox_5_currentTextChanged(const QString &arg1);

private:
    Ui::AdminWin *ui;
    QSqlQueryModel *model_res;
};

#endif // ADMINWIN_H
