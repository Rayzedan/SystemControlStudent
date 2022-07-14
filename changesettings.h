#ifndef CHANGESETTINGS_H
#define CHANGESETTINGS_H

#include <QDialog>

namespace Ui {
class ChangeSettings;
}

class ChangeSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeSettings(QWidget *parent = nullptr);
    ~ChangeSettings();

private:
    Ui::ChangeSettings *ui;
};

#endif // CHANGESETTINGS_H
