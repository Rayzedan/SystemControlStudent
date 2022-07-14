#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QCommonStyle>
#include "departedit.h"
#include "courseedit.h"
#include "questionedit.h"
#include "topicedit.h"
#include "basewindow.h"
#include "resultswindow.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

signals:
    void firstWindow(); // Сигнал для соединения окна администратора и окна авторизации
    void backToAuth(); // Сигнал для возвращения к начальному окну приложения

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_ButDeppart_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AdminWindow *ui;
    questionedit *questForm;
    departedit *departForm;
    courseedit *courseForm;
    topicedit *topicForm;
    BaseWindow *baseForm;
    ResultsWindow *resultForm;
};

#endif // ADMINWINDOW_H
