#ifndef FILLRESULT_H
#define FILLRESULT_H

#include <QWidget>

namespace Ui {
class FillResult;
}

class FillResult : public QWidget
{
    Q_OBJECT

public:
    explicit FillResult(QWidget *parent = nullptr);
    ~FillResult();

private:
    Ui::FillResult *ui;
};

#endif // FILLRESULT_H
