#include "choosescene.h"
#include "ui_choosescene.h"
#include "restroom.h"
#include "gameintroduction.h"

#include "chapter1.h"
#include "chapter2.h"
#include "chapter3.h"


ChooseScene::~ChooseScene()
{
    delete ui;
}

void ChooseScene::VictorScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“胜利图片”
    QLabel *label=new QLabel(this);
    QPixmap Origin(":/image/GameOver.png");
    QPixmap pixmap=Origin.scaled(Origin.size()*0.8,Qt::KeepAspectRatio);
    label->setPixmap(pixmap);
    label->setGeometry(centerX-pixmap.width()/2,-pixmap.height(),pixmap.width(),pixmap.height());
    //创建出现胜利的动画,从顶部跳跃到中心
    QPropertyAnimation *victoryAnimation=new QPropertyAnimation(label,"geometry",this);
    victoryAnimation->setDuration(1000);
    victoryAnimation->setStartValue(QRect(centerX - pixmap.width() / 2, -pixmap.height(), pixmap.width(), pixmap.height()));
    victoryAnimation->setEndValue(QRect(centerX - pixmap.width() / 2, centerY - pixmap.height() / 2, pixmap.width(), pixmap.height()));
    victoryAnimation->setEasingCurve(QEasingCurve::OutBounce);
    //停留2秒
    QPropertyAnimation *stayAnimation=new QPropertyAnimation(label,"geometry",this);
    stayAnimation->setDuration(2000);
    stayAnimation->setStartValue(victoryAnimation->endValue());
    stayAnimation->setEndValue(victoryAnimation->endValue());
    //连接停留动画的finished()信号到槽函数，用于动画完成后删除相关对象
    connect(stayAnimation,&QPropertyAnimation::finished,label,&QObject::deleteLater);
    connect(stayAnimation,&QPropertyAnimation::finished,stayAnimation,&QObject::deleteLater);
    //跳跃动画后启动悬停动画
    connect(victoryAnimation,&QPropertyAnimation::finished,[=](){
        stayAnimation->start();
    });
    //victoryAnimation->start();
}

void ChooseScene::GameOverScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“游戏结束图片”
    QLabel *label=new QLabel(this);
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
    qDebug()<<"animation";
}

void ChooseScene::on_pushButton_clicked()
{
    RestRoom *r=new RestRoom;
    this->close();
    r->show();
}

ChooseScene::ChooseScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChooseScene)
{
    ui->setupUi(this);
    this->setFixedSize(850,640);
    //设置背景图片
    QString imagePath=":/image/Map.png";//设置背景图片路径
    //检查图片是否存在
    if (QFile::exists(imagePath)){
        QPixmap backgroundImage(imagePath);
        if (!backgroundImage.isNull()) {
            //backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);// 调整图片尺寸以适应窗口大小
            QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
            this->setPalette(palette);
        }
    }
}


void ChooseScene::on_chapter1_btn_clicked()
{
    this->close();
    GameIntroduction *g=new GameIntroduction;
    g->Introduction1();
    g->show();
}


void ChooseScene::on_chapter2_btn_clicked()
{
    this->close();
    GameIntroduction *g=new GameIntroduction;
    g->Introduction2();
    g->show();
}

void ChooseScene::on_chapter3_btn_clicked()
{
    this->close();
    GameIntroduction *g=new GameIntroduction;
    g->Introduction3();
    g->show();
}

