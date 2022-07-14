#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "questionedit.h"
#include "changesettings.h"

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

signals:
    void backToAdm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::BaseWindow *ui;
    questionedit *questForm;
    ChangeSettings *changeSet;
};

#endif // BASEWINDOW_H
