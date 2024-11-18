#ifndef CHAPTER2PILLARITEM_H
#define CHAPTER2PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Chapter2PillarItem:public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY (qreal x READ x WRITE setX) //让柱子左右移动
public:
    Chapter2PillarItem();
    ~Chapter2PillarItem();   //析构函数：确保当该柱子在界面消失时，该对象也消失
    qreal x() const;
    void setX(qreal x);
    void freezeInPlace();
signals:
    void collideFail();

public slots:


private:
    bool collidesWithFish();

    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;
    qreal m_x;
    int yPos;
    bool getCoin;   //注意注意后续要把这个挪到金币的头文件中

    QPropertyAnimation *xAnimation;
};

#endif // CHAPTER2PILLARITEM_H
