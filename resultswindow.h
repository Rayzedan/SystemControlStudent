#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent = nullptr);
    ~ResultsWindow();

private:
    Ui::ResultsWindow *ui;
    QSqlQueryModel *model_res;
};

#endif // RESULTSWINDOW_H
