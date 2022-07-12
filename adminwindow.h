#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "departedit.h"
#include "courseedit.h"
#include "questionedit.h"
#include "topicedit.h"
namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_ButDeppart_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
