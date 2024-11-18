#include "chapter2scene.h"
#include "chapter2pillaritem.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Chapter2Scene::Chapter2Scene (QObject *parent)
    : QGraphicsScene{parent},gameOn(true)
{
    setUpPillarTimer();
}

void Chapter2Scene::addFish()
{
    fish=new Chapter2FishItem(QPixmap(":/image/Chapter2/fishup.png"));   //创建鱼的对象
    addItem(fish);   //将图像添加到背景
}

bool Chapter2Scene::getGameOn() const
{
    return gameOn;
}

void Chapter2Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Chapter2Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Space){
        if (gameOn){
            fish->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Chapter2Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button()==Qt::LeftButton){//当按鼠标左键
        if (gameOn){
            fish->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Chapter2Scene::VictorScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“游戏结束图片”
    QLabel *label=new QLabel();
    QPixmap Origin(":/image/victory.png");
    QPixmap Pixmap=Origin.scaled(Origin.size()*0.8,Qt::KeepAspectRatio);
    label->setPixmap(Pixmap);
    label->setGeometry(centerX-Pixmap.width()/2,-Pixmap.height(),Pixmap.width(),Pixmap.height());
    //创建出现的动画,从顶部跳跃到中心
    QPropertyAnimation *overAnimation=new QPropertyAnimation(label,"geometry",this);
    overAnimation->setDuration(1000);
    overAnimation->setStartValue(QRect(centerX - Pixmap.width() / 2, -Pixmap.height(), Pixmap.width(), Pixmap.height()));
    overAnimation->setEndValue(QRect(centerX - Pixmap.width() / 2, centerY - Pixmap.height() / 2, Pixmap.width(), Pixmap.height()));
    overAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //停留2秒
    QPropertyAnimation *stayAnimation=new QPropertyAnimation(label,"geometry",this);
    stayAnimation->setDuration(2000);
    stayAnimation->setStartValue(overAnimation->endValue());
    stayAnimation->setEndValue(overAnimation->endValue());
    //连接停留动画的finished()信号到槽函数，用于动画完成后删除相关对象
    connect(stayAnimation,&QPropertyAnimation::finished,label,&QObject::deleteLater);
    connect(stayAnimation,&QPropertyAnimation::finished,stayAnimation,&QObject::deleteLater);
    //跳跃动画后启动悬停动画
    connect(overAnimation,&QPropertyAnimation::finished,[=](){
        stayAnimation->start();
    });
    overAnimation->start();
    label->show();
    qDebug()<<"animation";
}

void Chapter2Scene::GameOverScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“游戏结束图片”
    QLabel* label=new QLabel();
    QPixmap Origin(":/image/GameOver.png");
    QPixmap Pixmap=Origin.scaled(Origin.size()*0.8,Qt::KeepAspectRatio);
    label->setPixmap(Pixmap);
    label->setGeometry(centerX-Pixmap.width()/2,-Pixmap.height(),Pixmap.width(),Pixmap.height());
    //创建出现的动画,从顶部跳跃到中心
    QPropertyAnimation *overAnimation=new QPropertyAnimation(label,"geometry",this);
    overAnimation->setDuration(1000);
    overAnimation->setStartValue(QRect(centerX - Pixmap.width() / 2, -Pixmap.height(), Pixmap.width(), Pixmap.height()));
    overAnimation->setEndValue(QRect(centerX - Pixmap.width() / 2, centerY - Pixmap.height() / 2, Pixmap.width(), Pixmap.height()));
    overAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //停留2秒
    /*
    QPropertyAnimation *stayAnimation=new QPropertyAnimation(label,"geometry",this);
    stayAnimation->setDuration(2000);
    stayAnimation->setStartValue(overAnimation->endValue());
    stayAnimation->setEndValue(overAnimation->endValue());
    //连接停留动画的finished()信号到槽函数，用于动画完成后删除相关对象
    connect(stayAnimation,&QPropertyAnimation::finished,label,&QObject::deleteLater);
    connect(stayAnimation,&QPropertyAnimation::finished,stayAnimation,&QObject::deleteLater);
    //跳跃动画后启动悬停动画
    connect(overAnimation,&QPropertyAnimation::finished,[=](){
        stayAnimation->start();
    });
    */
    overAnimation->start();
    label->show();
    qDebug()<<"animation";
}

void Chapter2Scene::setUpPillarTimer()
{
    pillarTimer=new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){   //当计时结束
        Chapter2PillarItem* PillarItem=new Chapter2PillarItem();

        connect(PillarItem,&Chapter2PillarItem::collideFail,[=](){
            pillarTimer->stop();
            freezeFishAndPillarsInPlace();
            setGameOn(false);
            GameOverScene();
            qDebug()<<"碰撞后，跳出GameOver动画";
        });
        addItem(PillarItem);
    });
    pillarTimer->start(1000);
}

void Chapter2Scene::freezeFishAndPillarsInPlace()
{
    fish->freezeInPlace();//使水母静止
    //使(当前在该页面的)海藻停止移动
    QList<QGraphicsItem *>sceneItems=items();
    foreach (QGraphicsItem *item, sceneItems){
        Chapter2PillarItem* pillar=dynamic_cast<Chapter2PillarItem*>(item);
        if (pillar){
            pillar->freezeInPlace();
        }
    }
}

