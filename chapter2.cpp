#include "chapter2.h"
#include "ui_chapter2.h"
#include "choosescene.h"
#include "gameintroduction.h"
#include "chapter1.h"
#include <QGraphicsPixmapItem>
#include <QMovie>
#include <QMessageBox>

Chapter2::Chapter2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chapter2)
{
    ui->setupUi(this);
    //背景设置
    scene=new Chapter2Scene (this);
    scene->setSceneRect(-425,-320,850,640);//(x,y,w,h)
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/image/Chapter2/sea.png"));
    scene->addItem(pixItem);    //添加背景
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,pixItem->boundingRect().height()/2));
    scene->addFish();//先添加背景，再在背景上添加小鱼
    ui->graphicsView->setScene(scene);
    //进度条
    ui->progressBar->setMaximum(30*1000);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(30*1000);
    ui->progressBar->setStyleSheet("QProgressBar{border-radius:5px;background:white;} QProgressBar::chunk{border-radius:5px;background:blue}");
    //游戏计时器
    gameTimer=new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(GameTimeEvent()));//再次打开时更新时间条
    gameTimer->start(kGameTimerInterval);
}

Chapter2::~Chapter2()
{
    delete ui;
}

void Chapter2::on_Back_clicked()
{
    this->close();
    ChooseScene *c=new ChooseScene;
    c->show();
}

void Chapter2::GameTimeEvent()
{
    //进度条效果设计
    if (ui->progressBar->value()==0){
        gameTimer->stop();
        //scene->VictorScene();
    }else{
        ui->progressBar->setValue(ui->progressBar->value()-kGameTimerInterval);
    }
}

