#ifndef COURSEEDIT_H
#define COURSEEDIT_H

#include <QDialog>

namespace Ui {
class courseedit;
}

class courseedit : public QDialog
{
    Q_OBJECT

public:
    explicit courseedit(QWidget *parent = nullptr);
    ~courseedit();

private:
    Ui::courseedit *ui;
};

#endif // COURSEEDIT_H
