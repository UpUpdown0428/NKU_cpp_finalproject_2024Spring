#include "chapter2pillaritem.h"
#include "chapter2scene.h"
#include "chapter2fishitem.h"

#include <QRandomGenerator> //用于使柱子从左到右移动
#include <QDebug>
#include <QGraphicsScene>

Chapter2PillarItem::Chapter2PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/image/Chapter2/seawead.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/image/Chapter2/seawead.png")))
{
    topPillar->setPos(QPointF(0,0)-QPointF(topPillar->boundingRect().width()/2,topPillar->boundingRect().height()+100));//设置上柱子的位置
    bottomPillar->setPos(QPointF(0,0)-QPointF(bottomPillar->boundingRect().width()/2,60));//设置下柱子的位置

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos=QRandomGenerator::global()->bounded(350);  //随机y的位置 0-150
    int xRandomizer = QRandomGenerator::global()->bounded(10);  //随机产生x的位置
    setPos(QPoint(0,0)+QPoint(350+xRandomizer,yPos)); //确定柱子的位置
    xAnimation=new QPropertyAnimation(this,"x",this);  //移动x轴上位置
    xAnimation->setStartValue(500+xRandomizer);  //开始的位置
    xAnimation->setEndValue(-500);  //结束的位置
    xAnimation->setEasingCurve(QEasingCurve::Linear);//移动的方式
    xAnimation->setDuration(1500);


    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

Chapter2PillarItem::~Chapter2PillarItem()
{
    qDebug()<<"Deleting Pillar";
}

qreal Chapter2PillarItem::x() const
{
    return m_x;
}

void Chapter2PillarItem::setX(qreal x)
{
    qDebug()<<"Pillar position:"<<x;
    m_x = x;

    if (collidesWithFish()){
        emit collideFail();

    }
    setPos(QPointF(0,0)+QPointF(x,yPos));
}

void Chapter2PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

bool Chapter2PillarItem::collidesWithFish()
{
    QList<QGraphicsItem*>collidingItems=topPillar->collidingItems();  //一个列出与上海藻碰撞的物体的列表
    collidingItems.append(bottomPillar->collidingItems());  //列出与下海藻碰撞的物体的列表

    foreach (QGraphicsItem* Item, collidingItems) {
        Chapter2FishItem* fishItem=dynamic_cast<Chapter2FishItem*>(Item);//使列表中的物体指向水母
        if (fishItem){
            return true;
        }
    }
    return false;
}
