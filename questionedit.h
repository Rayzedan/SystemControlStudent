#ifndef QUESTIONEDIT_H
#define QUESTIONEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QStackedWidget>
#include <QCloseEvent>


namespace Ui {
class questionedit;
}

class questionedit : public QDialog
{
    Q_OBJECT

public:
    explicit questionedit(QWidget *parent = nullptr);
    ~questionedit();

signals:
    void backToAdm();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::questionedit *ui;
    //QStackedWidget *stackedWidget;
};

#endif // QUESTIONEDIT_H
