#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "questionedit.h"

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::BaseWindow *ui;
    questionedit *questForm;
};

#endif // BASEWINDOW_H
