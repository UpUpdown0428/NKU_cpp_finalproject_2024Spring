#include "chapter2fishitem.h"
#include "qpixmap.h"
#include <QTimer>
#include <QGraphicsScene>

Chapter2FishItem::Chapter2FishItem(QPixmap pixmap):wingPosition(WingPosition::Up),wingDirection(0)
{
    setPixmap(pixmap);

    QTimer* fishWingsTimer=new QTimer(this);   //设置鱼的翅膀什么时候更新
    connect(fishWingsTimer,&QTimer::timeout,[=](){     //当计时结束时，更新翅膀图像
        updatepixmap();
    });
    fishWingsTimer->start(80);

    groundPosition=scenePos().y()+290;

    yAnimation=new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);
    yAnimation->start();

    rotationAnimation=new QPropertyAnimation(this,"rotation",this);
    rotateTo(90,1200,QEasingCurve::InQuad);
}

qreal Chapter2FishItem::rotation() const
{
    return m_rotation;
}

qreal Chapter2FishItem::y() const
{
    return m_y;
}

void Chapter2FishItem::shootUp()
{
    yAnimation->stop();//停止下降
    rotationAnimation->stop();//停止旋转

    qreal curPosY=y();   //要上升时小鱼的纵坐标
    yAnimation->setStartValue(curPosY);     //纵坐标的动画开始的位置
    yAnimation->setEndValue(curPosY-scene()->sceneRect().height()/8);  //纵坐标动画结束的位置：y-scene的高/8
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);    //小鱼以何种曲线上升
    yAnimation->setDuration(285);    //上升时间

    connect(yAnimation,&QPropertyAnimation::finished,[=]{  //当这个动画（小鱼向上）结束时
        fallToGroundIfNecessary();
    });
    yAnimation->start();  //开始上升这个动画
    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void Chapter2FishItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void Chapter2FishItem::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    //进行旋转操作
    QPointF c=boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),c.y());
    setTransform(t);
}

void Chapter2FishItem::setY(qreal newY)
{
    moveBy(0,newY-m_y);  //移动的距离（x,y)
    m_y = newY;
}

void Chapter2FishItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}


void Chapter2FishItem::fallToGroundIfNecessary()
{
    if (y()<groundPosition){ //当小鱼纵坐标小于地面
        rotationAnimation->stop();    //旋转停止
        //yAnimation->stop();   //纵坐标变化（即向上）停止
        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200); //动画持续时间
        yAnimation->start();

        rotateTo(90,1100,QEasingCurve::InCubic);

    }
}

void Chapter2FishItem::updatepixmap()
{
    if (wingPosition == WingPosition::Middle){   //当翅膀在中间时
        if (wingDirection){    //翅膀向上
            //up
            setPixmap(QPixmap(":/image/Chapter2/fishup.png"));      //呈现向上的图像
            wingPosition=WingPosition::Up;
            wingDirection=0;                                       //翅膀变为向下
        }else{
            //Down
            wingPosition=WingPosition::Middle;
            setPixmap(QPixmap(":/image/Chapter2/fishdown.png"));     //呈现向下的图像
            wingPosition=WingPosition::Down;
            wingDirection=1;                                        //翅膀变为向上
        }
    }else{
        setPixmap(QPixmap(":/image/Chapter2/fishmiddle.png"));             //当翅膀不在中间时，使其在中间
        wingPosition=WingPosition::Middle;
    }
}
