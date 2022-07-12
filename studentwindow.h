#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

signals:
    void firstWindow();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
