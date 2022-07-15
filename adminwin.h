#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>
#include <tabwidget.h>

namespace Ui {
class AdminWin;
}

class AdminWin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWin(QWidget *parent = nullptr);
    ~AdminWin();

private:
    Ui::AdminWin *ui;
};

#endif // ADMINWIN_H
