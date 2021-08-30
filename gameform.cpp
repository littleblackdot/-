#include "gameform.h"
#include "ui_gameform.h"

#include<iostream>
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);
    this->setFixedSize(360, 600);
    score = 0;
    timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(blockMove()));
}

GameForm::~GameForm()
{
    delete ui;
}


int GameForm:: getRandomNum(){
    int randn;
    QTime time = QTime::currentTime();
    qsrand(time.msec()*qrand()*qrand()*qrand()*qrand());//初始化随机数种子
    randn = qrand()%4;//生成0 - 3之间的随机数
    return randn;
}

void GameForm::blockMove()
{
    int pos_y = blockDeque.back()->pos().y();
    if(pos_y < 0){
        pos_y = pos_y+150;
    }
    if((pos_y)%150 > (pos_y+speed*3)%150){//最下面一排的块移动了一格， 最上面需要生成一派新的块
        BlackBlockFactory *bFactory = BlackBlockFactory::getInstance();
        WhiteBlockFactory *wFactory = WhiteBlockFactory::getInstance();
        int seq = getRandomNum();
        for(int j=0; j<4; j++){
            Block *b1;
            b1 = seq == j ?  bFactory->createBlock(this) : wFactory->createBlock(this);
            b1->setShape();
            b1->move((3-j)*90, -150);
            b1->stackUnder(ui->widget);
            b1->show();
            blockDeque.push_front(b1);
        }
        if(pos_y >= 600){//块运动出了显示区域，需要移除
          int flag = 0;
          for(int i=0; i<4; i++){
              if(BLACK == blockDeque.back()->getColor()){
                    flag = 1;
                    std::cout <<  blockDeque.back()->pos().x()/90+(blockDeque.back()->pos().y()/150)*4<<std::endl;
              }
             delete blockDeque.back();
             blockDeque.pop_back();
          }
          if(1 == flag){
              cout<< "over by move" << endl;
              gameOver();
          }
      }
    }
    //每个块都向下移动
    for(auto i = 0; i < (int)blockDeque.size(); i++){
        blockDeque[i]->down(speed);
    }
}


void GameForm::formInit(int speed){
    timer->start(20);
    BlackBlockFactory *bFactory = BlackBlockFactory::getInstance();
    WhiteBlockFactory *wFactory = WhiteBlockFactory::getInstance();
    this->speed  = speed;
    score = 0;
    //初始时，生成一排块
    int seq = getRandomNum();
    for(int i=0; i<4; i++){
            Block *b1;
            b1 = seq == i ?  bFactory->createBlock(this) : wFactory->createBlock(this);
            b1->setShape();
            b1->move((3-i)*90, -150);
            b1->stackUnder(ui->widget);
            b1->show();
            blockDeque.push_front(b1);
    }
}


void GameForm::mousePressEvent(QMouseEvent *event){
    int x = event->x()/90;
    int y = event->y()/150;
    int index = y*4+x;

    if(event->y() > blockDeque[index]->pos().y()+150 ){
        index = (y+1)*4+x;
    }
    if(index < (int)blockDeque.size()){
        if(blockDeque[index]->getColor() == WHITE){
            cout<< "over by clicked" << endl;
            gameOver();
        }else{
            Block *temp = blockDeque[index];
            WhiteBlockFactory *wFactory = WhiteBlockFactory::getInstance();
            blockDeque[index] = wFactory->createBlock(this);
            blockDeque[index]->setShape();
            blockDeque[index]->move(temp->pos());
            temp->hide();
            blockDeque[index]->show();
            score++;
            ui->lcdNumber->display(score);
            delete temp;
        }
    }
}

void GameForm:: gameOver(){
    timer->stop();

    for(int i=0; i<blockDeque.size(); i++){
        cout << blockDeque[i]->getColor()<< " ";
        if(i%4 == 3){
            cout<<endl;
        }
    }
//    while(blockDeque.size() > 0){
//        blockDeque.front()->hide();
//        delete blockDeque.front();
//        blockDeque.pop_front();
//    }
    QString str = QString("得分：%1 \n再玩一次？").arg(score);
    int ret = QMessageBox::question(this, "游戏结束", str);
    if( QMessageBox::Yes == ret){
        formInit(speed);
    }else{
        this->close();
        Widget *menuFrom = new Widget;
        menuFrom->show();
    }
}

