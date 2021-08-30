#include "widget.h"
#include "ui_widget.h"
#include "gameform.h"

#include <QFile>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->move(600, 200);
    this->setWindowTitle(QString("别踩白块儿"));
    this->setFixedSize(360, 600);   //5行4列
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/110.jpeg")));
    setPalette(pal);

    settingsForm = new SettingsForm;
    settingsForm->setSpeed(1);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    GameForm *gameForm = new GameForm;
    gameForm->move(this->pos());
    gameForm->formInit(settingsForm->getSpeed());
    gameForm->show();
    this->close();
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}

void Widget::on_pushButton_3_clicked()
{

    settingsForm->move(this->pos());
    settingsForm->show();
}

void Widget::on_pushButton_4_clicked()
{
    QMessageBox::information(this, QString("config"), QString("Version1.0"), QMessageBox::Cancel, QMessageBox::Cancel);
}
