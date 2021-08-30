#include "block.h"

Block::Block(Color color, QWidget *parent):color(color), QWidget(parent){}

Color Block::getColor(){return color;}

void Block::setColor(Color color){this->color = color;}

void Block::down(int speed){
    int offset = (150 * 20) * speed / 1000 ;
    this->move(this->pos().x(), this->pos().y() + offset);
}


BlackBlock:: BlackBlock(QWidget *parent): Block(BLACK, parent){}

void BlackBlock::setShape(){
    this->setStyleSheet("background-color:black;");
    this->resize(90, 150);
}

WhiteBlock:: WhiteBlock(QWidget *parent): Block(WHITE, parent){}

void WhiteBlock::setShape(){
    this->setStyleSheet("background-color:white;");
    this->resize(90, 150);
}

Block* BlackBlockFactory::createBlock(QWidget *parent){
    Block* block = new BlackBlock(parent);
    return block;
}

BlackBlockFactory* BlackBlockFactory::getInstance(){
    static BlackBlockFactory *factory = nullptr;
    if(factory == nullptr){
        factory = new BlackBlockFactory;
    }
    return factory;
}

Block* WhiteBlockFactory::createBlock(QWidget *parent){
    Block* block = new WhiteBlock(parent);
    return block;
}

WhiteBlockFactory* WhiteBlockFactory::getInstance(){
    static WhiteBlockFactory *factory = nullptr;
    if(factory == nullptr){
        factory = new WhiteBlockFactory;
    }
    return factory;
}
