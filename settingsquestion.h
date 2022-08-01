#ifndef SETTINGSQUESTION_H
#define SETTINGSQUESTION_H

#include <QDialog>

namespace Ui {
class SettingsQuestion;
}

class SettingsQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsQuestion(QWidget *parent = nullptr);
    ~SettingsQuestion();

private:
    Ui::SettingsQuestion *ui;
};

#endif // SETTINGSQUESTION_H
