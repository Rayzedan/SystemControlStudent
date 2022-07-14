#ifndef TOPICEDIT_H
#define TOPICEDIT_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class topicedit;
}

class topicedit : public QDialog
{
    Q_OBJECT

public:
    explicit topicedit(QWidget *parent = nullptr);
    ~topicedit();

signals:
    void backToAdm();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::topicedit *ui;
};

#endif // TOPICEDIT_H
