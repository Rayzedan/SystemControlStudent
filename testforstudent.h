#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class TestForStudent;
}

class TestForStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestForStudent(QWidget *parent = nullptr);
    ~TestForStudent();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::TestForStudent *ui;
};

#endif // TESTFORSTUDENT_H
