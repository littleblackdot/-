#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <iostream>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();
    int getSpeed();
    void setSpeed(int Speed);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::SettingsForm *ui;
    int speed;
};

#endif // SETTINGSFORM_H
