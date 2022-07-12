#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
