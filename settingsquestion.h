#ifndef SETTINGSQUESTION_H
#define SETTINGSQUESTION_H

#include <QDialog>
#include <QSqlQuery>
#include "database.h"

namespace Ui {
class SettingsQuestion;
}

class SettingsQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsQuestion(QVariantList data, QWidget *parent = nullptr);
    ~SettingsQuestion();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();


private:
    Ui::SettingsQuestion *ui;
    QVariantList data;
    DataBase *db;
};

#endif // SETTINGSQUESTION_H
