#ifndef CHAPTER2SCENE_H
#define CHAPTER2SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include "chapter2fishitem.h"

class Chapter2Scene:public QGraphicsScene
{
    Q_OBJECT
public:
    Chapter2Scene(QObject *parent);

    void addFish();
    void VictorScene();
    void GameOverScene();
    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    bool gameOn;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void setUpPillarTimer();//建立一个计时器，在间隙添加柱子
    void freezeFishAndPillarsInPlace();

    QTimer *pillarTimer;
    Chapter2FishItem* fish;
    QLabel* LabelForBackground;

};

#endif // CHAPTER2SCENE_H
