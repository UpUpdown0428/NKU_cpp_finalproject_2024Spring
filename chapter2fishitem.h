#ifndef CHAPTER2FISHITEM_H
#define CHAPTER2FISHITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Chapter2FishItem:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY);

    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation );       
public:   
    qreal rotation() const;

    Chapter2FishItem(QPixmap pixmap);
    qreal y() const;

    void shootUp();//控制鱼向上
    void freezeInPlace();
public slots:
    void setRotation(qreal newRotation);
    void rotateTo (const qreal &end, const int& duration, const QEasingCurve& curve);
    void setY(qreal newY);
    void fallToGroundIfNecessary();

private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };

    void updatepixmap();
    WingPosition wingPosition;
    bool wingDirection;//0:down   1:up
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation* yAnimation; //定义y上的动画
    QPropertyAnimation* rotationAnimation;  //定义旋转的动画
    qreal groundPosition;   //地板的位置
};

#endif // CHAPTER2FISHITEM_H
