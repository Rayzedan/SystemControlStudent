#ifndef TESTFORSTUDENT_H
#define TESTFORSTUDENT_H

#include <QMainWindow>

namespace Ui {
class TestForStudent;
}

class TestForStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestForStudent(QWidget *parent = nullptr);
    ~TestForStudent();

private:
    Ui::TestForStudent *ui;
};

#endif // TESTFORSTUDENT_H
