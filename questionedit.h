#ifndef QUESTIONEDIT_H
#define QUESTIONEDIT_H

#include <QDialog>

namespace Ui {
class questionedit;
}

class questionedit : public QDialog
{
    Q_OBJECT

public:
    explicit questionedit(QWidget *parent = nullptr);
    ~questionedit();

private:
    Ui::questionedit *ui;
};

#endif // QUESTIONEDIT_H
