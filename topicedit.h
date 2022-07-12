#ifndef TOPICEDIT_H
#define TOPICEDIT_H

#include <QDialog>

namespace Ui {
class topicedit;
}

class topicedit : public QDialog
{
    Q_OBJECT

public:
    explicit topicedit(QWidget *parent = nullptr);
    ~topicedit();

private:
    Ui::topicedit *ui;
};

#endif // TOPICEDIT_H
