#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "block.h"
#include "widget.h"
#include <QWidget>
#include <deque>
#include <QTimer>

using namespace std;

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = nullptr);
    ~GameForm();
    void formInit(int speed);
private:
    Ui::GameForm *ui;
    deque<Block*> blockDeque;
    int score;
    int speed;
    QTimer *timer;
    void formReset();
    void gameOver();
    int getRandomNum();
    void mousePressEvent(QMouseEvent *event);
private slots:
    void blockMove();
    void clickBlock(Block*);
};

#endif // GAMEFORM_H
