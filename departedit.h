#ifndef DEPARTEDIT_H
#define DEPARTEDIT_H

#include <QDialog>

namespace Ui {
class departedit;
}

class departedit : public QDialog
{
    Q_OBJECT

public:
    explicit departedit(QWidget *parent = nullptr);
    ~departedit();

private:
    Ui::departedit *ui;
};

#endif // DEPARTEDIT_H
