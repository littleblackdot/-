#ifndef BLOCK_H
#define BLOCK_H
#include <QWidget>


enum Color{
    BLACK, WHITE
};

//抽象产品
class Block: public QWidget{

private:
        Color color;
public:
        explicit Block(Color color, QWidget *parent = nullptr);
        Color getColor();
        void setColor(Color color);
        void down(int speed = 1);
        virtual void setShape() = 0;
};

class BlackBlock: public Block{
public:
    BlackBlock(QWidget *parent);
    void setShape();
};


class WhiteBlock: public Block{
public:
    WhiteBlock(QWidget *parent);
    void setShape();
};

//抽象工厂
class BlockFactory{
public:
    virtual Block* createBlock() = 0;
};

//单例实体工厂
class BlackBlockFactory{
private:
    BlackBlockFactory(){}
public:
    Block* createBlock(QWidget *parent = nullptr);
    static BlackBlockFactory* getInstance();
};


//单例实体工厂
class WhiteBlockFactory{
private:
    WhiteBlockFactory(){}
public:
    Block* createBlock(QWidget *parent = nullptr);
    static WhiteBlockFactory* getInstance();
};




#endif // BLOCK_H
