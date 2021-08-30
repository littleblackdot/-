#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    speed = 1;
    this->setFixedSize(360, 600);
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(10);
    ui->horizontalSlider->setSingleStep(1);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

int SettingsForm::getSpeed()
{
    return speed;
}

void SettingsForm::setSpeed(int Speed)
{
    this->speed = Speed;
}

void SettingsForm::closeEvent(QCloseEvent *event)
{
    this->hide();
}

void SettingsForm::on_horizontalSlider_valueChanged(int value)
{
    speed = ui->horizontalSlider->value();
    ui->label_2->setText(QString("%1").arg(speed));
}

void SettingsForm::on_horizontalSlider_sliderMoved(int position)
{
    //speed = ui->horizontalSlider->value();
    //std::cout<<<<std::endl;
    //ui->label_2->setText(QString("%1").arg(speed));
    //ui->label_2->show();
}
