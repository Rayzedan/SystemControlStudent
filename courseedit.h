#ifndef COURSEEDIT_H
#define COURSEEDIT_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class courseedit;
}

class courseedit : public QDialog
{
    Q_OBJECT

public:
    explicit courseedit(QWidget *parent = nullptr);
    ~courseedit();

signals:
    void backToAdm();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::courseedit *ui;
};

#endif // COURSEEDIT_H
