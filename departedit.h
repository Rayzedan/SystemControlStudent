#ifndef DEPARTEDIT_H
#define DEPARTEDIT_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class departedit;
}

class departedit : public QDialog
{
    Q_OBJECT

public:
    explicit departedit(QWidget *parent = nullptr);
    ~departedit();

signals:
    void backToAdm();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::departedit *ui;
};

#endif // DEPARTEDIT_H
