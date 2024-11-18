#include "gameintroduction.h"
#include "qpixmap.h"
#include "restroom.h"
#include "choosescene.h"
#include "chapter1.h"
#include "chapter2.h"
#include "chapter3.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

GameIntroduction::GameIntroduction(QWidget *parent)
    : QWidget(parent)

{
    resize(850,640);
}

GameIntroduction::~GameIntroduction(){}

void GameIntroduction::Background()
{
    QLabel *label=new QLabel(this);
    label->setPixmap(QPixmap(backgroundImagePath));
    label->setGeometry(0,0,850,640);
    label->show();
    qDebug()<<"set background";
}

void GameIntroduction::mainIntoduction()
{
    //characterImagePath1=":/image/Deng1.png";
    //characterImagePath2=":/image/Deng2.png";
    backgroundImagePath=":/image/Background4.png";
    Background();
    //CharacterAnimation Deng;
    QLabel *Deng=new QLabel(this);
    Deng->setPixmap(QPixmap(":/image/Deng1.png"));
    Deng->setGeometry(0,80,400,540);
    Deng->show();
    QLabel *paper = new QLabel(this);
    paper->setGeometry(300,20,700,600);
    paper->setPixmap(QPixmap(":/image/paper.png"));
    paper->show();
    QLabel *title=new QLabel(this);
    title->setText("THE GOBLET OF FIRE");
    title->setFont(QFont("Harry P",35));
    title->move(410,100);
    title->show();
    QLabel *info=new QLabel(this);
    info->setGeometry(400,100,350,400);
    info->setWordWrap(true);
    info->setText("魔法世界时隔多年都未曾举办的三强争霸赛终\n"
                  "于在今年重振锣鼓，霍格沃茨，布斯巴顿，以及"
                  "德姆斯特朗学院将各派出一位勇士应战。\n"
                  "勇士们将经历三道考验，分别是：魔药重现，黑湖"
                  "探险，迷宫寻宝。这将考验勇士们的智力，体能和勇气。\n"
                  "最终胜者将获得火焰杯，成为世界最优秀的巫师,"
                  "但这场游戏同时也是极为危险的，\n"
                  "你愿意接受挑战吗？");
    info->setFont(QFont("仿宋",15));
    info->show();
    will=new QPushButton(this);
    will->setText("I do");
    will->setFont(QFont("Harry P",30));
    will->setStyleSheet("color:#635742;"
                        "background-color:#D1B890;"
                        "font-weight:bold;"
                        "text-align: center;"// 文本水平居中
                        "border-radius: 20px;"
                        "border-width: 2px;"
                        "border-color: #635742;"
                        "border-style: solid;"
                        "border-width: 5px;"
                        "border-color: #635742");
    will->setFixedSize(150, 50);
    will->move(500,460);
    will->show();

    connect(will, &QPushButton::clicked, this, &GameIntroduction::onButtonClick);
    qDebug()<<"运行了游戏介绍函数";


}

void GameIntroduction::Introduction1()
{
    backgroundImagePath=":/image/PotionClass.jpg";
    Background();
    QLabel *snp=new QLabel(this);
    QPixmap snpPicture(":/image/snp.png");
    snp->setPixmap(snpPicture);
    snp->setGeometry(440,150,410,500);
    QSize sz=snp->size();
    snp->setPixmap(snpPicture.scaled(sz));
    snp->raise();
    snp->show();

    QLabel *paper = new QLabel(this);
    QPixmap popupPixmap1(":/image/paper2.png");
    paper->setPixmap(popupPixmap1);
    paper->setGeometry(20,20,700,600);
    QGraphicsOpacityEffect *paperOpacity = new QGraphicsOpacityEffect(this);
    paperOpacity->setOpacity(0);
    paper->setGraphicsEffect(paperOpacity);
    QPropertyAnimation *Animation = new QPropertyAnimation(paperOpacity, "opacity");
    Animation->setDuration(500);
    Animation->setStartValue(0);
    Animation->setEndValue(1);
    Animation->start();

    QLabel *rule=new QLabel(this);
    QLabel *title=new QLabel(this);
    title->setText("Chapter1");
    title->setFont(QFont("Harry P",40));
    title->move(240,80);
    title->show();
    rule->setText("这道关卡考验是你的智识。\n复方汤剂是一种极难制作的药剂，\n这是一份秘方——\n"
                  "功效：喝下后可以变为想变成的任\n何生物（持续时间30秒）\n"
                  "                   \n"
                  "使用药剂：          \n"
                  "                   \n"
                  "                   \n"
                  "                   \n"
                  "                   \n"
                  "                   \n"
                  "制作方法：融合相同药剂\n"
                  "熬制时间：5分钟\n");
    rule->setFont(QFont("仿宋",20));
    rule->move(100,150);
    QPushButton *beginning=new QPushButton(this);
    beginning->setText("Begin!");
    beginning->setFont(QFont("Harry P",30));
    beginning->setStyleSheet("color:#635742;"
                        "background-color:#D1B890;"
                        "font-weight:bold;"
                        "text-align: center;"// 文本水平居中
                        "border-radius: 20px;"
                        "border-width: 2px;"
                        "border-color: #635742;"
                        "border-style: solid;"
                        "border-width: 5px;"
                        "border-color: #635742");
    beginning->setFixedSize(150, 50);
    beginning->move(240,530);
    connect(beginning, &QPushButton::clicked, this, [=]{
        Chapter1 *c=new Chapter1;
        this->close();
        c->show();
    });
}

void GameIntroduction::Introduction2()
{
    QLabel *Lake1=new QLabel(this);
    QPixmap Background1(":/image/Lake1.png");
    Lake1->setPixmap(Background1);
    Lake1->setGeometry(0,0,850,640);
    QGraphicsOpacityEffect *lake1Opacity = new QGraphicsOpacityEffect(this);
    lake1Opacity->setOpacity(0);
    Lake1->setGraphicsEffect(lake1Opacity);
    QPropertyAnimation *Animation1 = new QPropertyAnimation(lake1Opacity, "opacity");
    Animation1->setDuration(3000);
    Animation1->setStartValue(0);
    Animation1->setEndValue(1);

    QLabel *line1=new QLabel(this);
    line1->setText("霍格沃茨城堡旁的黑湖中藏有无尽的秘密和故事");
    line1->setFont(QFont("仿宋",20));
    line1->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation1 = new QPropertyAnimation(line1, "pos");
    PosAnimation1->setDuration(4000);
    PosAnimation1->setStartValue(QPoint(-200, 80));
    PosAnimation1->setEndValue(QPoint(250, 80));
    PosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line2=new QLabel(this);
    line2->setText("你最亲近的人被带到了湖底，\n等待着你的救援");
    line2->setFont(QFont("仿宋",20));
    line2->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation2 = new QPropertyAnimation(line2, "pos");
    PosAnimation2->setDuration(4000);
    PosAnimation2->setStartValue(QPoint(800, 160));
    PosAnimation2->setEndValue(QPoint(100, 160));
    PosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line3=new QLabel(this);
    line3->setText("通往湖底的路上，水藻丛生，危险至极,");
    line3->setFont(QFont("仿宋",20));
    line3->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation3 = new QPropertyAnimation(line3, "pos");
    PosAnimation3->setDuration(4000);
    PosAnimation3->setStartValue(QPoint(-200, 240));
    PosAnimation3->setEndValue(QPoint(250, 240));
    PosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line4=new QLabel(this);
    line4->setText("你需要伪装成水中生物，在水中呼吸");
    line4->setFont(QFont("仿宋",20));
    line4->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation4 = new QPropertyAnimation(line4, "pos");
    PosAnimation4->setDuration(4000);
    PosAnimation4->setStartValue(QPoint(800, 320));
    PosAnimation4->setEndValue(QPoint(100, 320));
    PosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line5=new QLabel(this);
    line5->setText("还记得第一关你获得的复方汤剂吗？");
    line5->setFont(QFont("仿宋",20));
    line5->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation5 = new QPropertyAnimation(line5, "pos");
    PosAnimation5->setDuration(6000);
    PosAnimation5->setStartValue(QPoint(-200, 400));
    PosAnimation5->setEndValue(QPoint(200, 400));
    PosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
    QParallelAnimationGroup *ParallelGroup1 = new QParallelAnimationGroup(this);
    ParallelGroup1->addAnimation(Animation1);
    ParallelGroup1->addAnimation(PosAnimation1);
    ParallelGroup1->addAnimation(PosAnimation2);
    ParallelGroup1->addAnimation(PosAnimation3);
    ParallelGroup1->addAnimation(PosAnimation4);
    ParallelGroup1->addAnimation(PosAnimation5);
    ParallelGroup1->start();

    QLabel *potion=new QLabel(this);
    QPixmap potionPixmap(":/image/Chapter1/Potion.png");
    potion->setPixmap(potionPixmap);
    potion->move(260,440);
    QGraphicsOpacityEffect *potionOpacity = new QGraphicsOpacityEffect(this);
    potionOpacity->setOpacity(0);
    potion->setGraphicsEffect(potionOpacity);
    QPropertyAnimation *Animation2 = new QPropertyAnimation(potionOpacity, "opacity");
    Animation2->setDuration(1000);
    Animation2->setStartValue(0);
    Animation2->setEndValue(1);

    QPushButton *next=new QPushButton(this);
    next->setText("Yes.Drink it.");
    next->move(450,480);
    next->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, "
                        "stop:0 rgba(53, 200, 68, 255), "
                        "stop:1 rgba(255, 255, 255, 255));"
                        "color: rgb(255, 255, 255);"
                        "border:0px groove gray;"
                        "border-radius:7px;padding:2px 4px");
    next->setFont(QFont("Harry P",25));
    next->setFixedSize(150, 50);
    QGraphicsOpacityEffect *nextOpacity = new QGraphicsOpacityEffect(this);
    nextOpacity->setOpacity(0);
    next->setGraphicsEffect(nextOpacity);
    QPropertyAnimation *Animation3 = new QPropertyAnimation(nextOpacity, "opacity");
    Animation3->setDuration(1000);
    Animation3->setStartValue(0);
    Animation3->setEndValue(1);

    QParallelAnimationGroup *ParallelGroup2 = new QParallelAnimationGroup(this);
    ParallelGroup2->addAnimation(Animation2);
    ParallelGroup2->addAnimation(Animation3);

    QSequentialAnimationGroup *Group = new QSequentialAnimationGroup(this);
    Group->addAnimation(ParallelGroup1);
    Group->addPause(500);
    Group->addAnimation(ParallelGroup2);
    Group->start();

    connect(next, &QPushButton::clicked, this, [=]{
        Chapter2 *c=new Chapter2;
        this->close();
        c->show();
    });
}

void GameIntroduction::Introduction3()
{
    QLabel *Lake1=new QLabel(this);
    QPixmap Background1(":/image/Forest.png");
    Lake1->setPixmap(Background1);
    Lake1->setGeometry(0,0,850,640);
    QGraphicsOpacityEffect *lake1Opacity = new QGraphicsOpacityEffect(this);
    lake1Opacity->setOpacity(0);
    Lake1->setGraphicsEffect(lake1Opacity);
    QPropertyAnimation *Animation1 = new QPropertyAnimation(lake1Opacity, "opacity");
    Animation1->setDuration(3000);
    Animation1->setStartValue(0);
    Animation1->setEndValue(1);

    QLabel *line1=new QLabel(this);
    line1->setText("恭喜你勇士，来到了最后一关");
    line1->setFont(QFont("仿宋",20));
    line1->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation1 = new QPropertyAnimation(line1, "pos");
    PosAnimation1->setDuration(4000);
    PosAnimation1->setStartValue(QPoint(-200, 80));
    PosAnimation1->setEndValue(QPoint(300, 80));
    PosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line2=new QLabel(this);
    line2->setText("火焰杯就蕴藏在这神秘的禁林中");
    line2->setFont(QFont("仿宋",20));
    line2->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation2 = new QPropertyAnimation(line2, "pos");
    PosAnimation2->setDuration(4000);
    PosAnimation2->setStartValue(QPoint(800, 160));
    PosAnimation2->setEndValue(QPoint(100, 160));
    PosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line3=new QLabel(this);
    line3->setText("禁林中的路交错复杂似迷宫,时有八眼巨蛛出现");
    line3->setFont(QFont("仿宋",20));
    line3->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation3 = new QPropertyAnimation(line3, "pos");
    PosAnimation3->setDuration(4000);
    PosAnimation3->setStartValue(QPoint(-200, 240));
    PosAnimation3->setEndValue(QPoint(250, 240));
    PosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line4=new QLabel(this);
    line4->setText("阴森至极不可就待，请在三分钟内找到火焰杯，拿到门钥匙，");
    line4->setFont(QFont("仿宋",20));
    line4->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation4 = new QPropertyAnimation(line4, "pos");
    PosAnimation4->setDuration(4000);
    PosAnimation4->setStartValue(QPoint(800, 320));
    PosAnimation4->setEndValue(QPoint(100, 320));
    PosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
    QLabel *line5=new QLabel(this);
    line5->setText("穿越到安全地带，否则将丧命禁林");
    line5->setFont(QFont("仿宋",20));
    line5->setStyleSheet("color:#ffffff");
    QPropertyAnimation *PosAnimation5 = new QPropertyAnimation(line5, "pos");
    PosAnimation5->setDuration(6000);
    PosAnimation5->setStartValue(QPoint(-200, 400));
    PosAnimation5->setEndValue(QPoint(200, 400));
    PosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
    QParallelAnimationGroup *ParallelGroup1 = new QParallelAnimationGroup(this);
    ParallelGroup1->addAnimation(Animation1);
    ParallelGroup1->addAnimation(PosAnimation1);
    ParallelGroup1->addAnimation(PosAnimation2);
    ParallelGroup1->addAnimation(PosAnimation3);
    ParallelGroup1->addAnimation(PosAnimation4);
    ParallelGroup1->addAnimation(PosAnimation5);

    QLabel *spider=new QLabel(this);
    QPixmap spiderPixmap(":/image/spider(1)(1).png");
    spider->setPixmap(spiderPixmap);
    QPropertyAnimation *Animation2_1 = new QPropertyAnimation(spider, "pos");
    Animation2_1->setDuration(2000);
    Animation2_1->setStartValue(QPoint(0, 0));
    Animation2_1->setEndValue(QPoint(800, 300));
    Animation2_1->setEasingCurve(QEasingCurve::InOutQuad);
    QPropertyAnimation *Animation2_2=new QPropertyAnimation(spider,"pos");
    Animation2_2->setDuration(2000);
    Animation2_2->setStartValue(QPoint(800, 250));
    Animation2_2->setEndValue(QPoint(0, 740));
    Animation2_2->setEasingCurve(QEasingCurve::InOutQuad);
    QSequentialAnimationGroup *Animation2 = new QSequentialAnimationGroup(this);
    Animation2->addAnimation(Animation2_1);
    Animation2->addAnimation(Animation2_2);
    QPushButton *next=new QPushButton(this);
    next->setText("Go to the Forbidden Forest!");
    next->move(320,480);
    next->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, "
                        "stop:0 rgba(53, 200, 68, 255), "
                        "stop:1 rgba(255, 255, 255, 255));"
                        "color: rgb(255, 255, 255);"
                        "border:0px groove gray;"
                        "border-radius:7px;padding:2px 4px");
    next->setFont(QFont("Harry P",25));
    next->setFixedSize(275, 50);
    QGraphicsOpacityEffect *nextOpacity = new QGraphicsOpacityEffect(this);
    nextOpacity->setOpacity(0);
    next->setGraphicsEffect(nextOpacity);
    QPropertyAnimation *Animation3 = new QPropertyAnimation(nextOpacity, "opacity");
    Animation3->setDuration(1000);
    Animation3->setStartValue(0);
    Animation3->setEndValue(1);

    QSequentialAnimationGroup *Group = new QSequentialAnimationGroup(this);
    Group->addAnimation(ParallelGroup1);
    Group->addPause(500);
    Group->addAnimation(Animation2);
    Group->addPause(500);
    Group->addAnimation(Animation3);
    Group->start();

    connect(next, &QPushButton::clicked, this, [=]{
        Chapter3 *c=new Chapter3;
        this->close();
        c->show();
    });
}

void GameIntroduction::onButtonClick()
{
    //当按钮被点击时
    backgroundImagePath=":/image/fire.png";
    Background();
    cupPopup = new QLabel(this);
    QPixmap popupPixmap(":/image/cup.png");
    cupPopup->setPixmap(popupPixmap);
    QPropertyAnimation *Animation1 = new QPropertyAnimation(cupPopup, "pos");//设置动画变量为pos即位置
    Animation1->setDuration(1000);//设置动画持续时间
    Animation1->setStartValue(QPoint(100, -600));//设置动画开始时的变量值
    Animation1->setEndValue(QPoint(100, 25));//设置动画结束时的变量值
    Animation1->setEasingCurve(QEasingCurve::InOutQuad);//设置动画曲线
    Animation1->start();
    QLabel *paper=new QLabel(this);
    QPixmap popupPixmap2(":/image/wrinckledPaper.png");
    paper->setPixmap(popupPixmap2);
    paper->setGeometry(470,200,500,200);
    QGraphicsOpacityEffect *paperOpacity = new QGraphicsOpacityEffect(this);
    paperOpacity->setOpacity(0);
    paper->setGraphicsEffect(paperOpacity);
    QPropertyAnimation *Animation2 = new QPropertyAnimation(paperOpacity, "opacity");
    Animation2->setDuration(1000);
    Animation2->setStartValue(0);
    Animation2->setEndValue(1);
    QLabel *congrat=new QLabel(this);
    congrat->setText("Congrats!\n"
                     "You're choosed by the Goblet of Fire\n"
                     "on behalf of the Hogwarts.");
    congrat->setFont(QFont("Harry P",24));
    congrat->move(490,220);
    QPushButton* yes=new QPushButton(this);
    yes->setText("I'm ready!");
    yes->setStyleSheet("color:#000000;"
                       "background-color:#C0C0C0;"
                       "font-weight:bold;"
                       "text-align: center;"// 文本水平居中
                       "border-radius: 20px;"
                       "border-width: 2px;"
                       "border-color: #000000;"
                       "border-style: solid;"
                       "border-width: 5px;"
                       "border-color: #000000");
    yes->setFont(QFont("Harry P",25));
    yes->setFixedSize(150, 50);
    yes->move(500,330);
    QGraphicsOpacityEffect *yesOpacity = new QGraphicsOpacityEffect(this);
    yesOpacity->setOpacity(0);
    yes->setGraphicsEffect(paperOpacity);
    QPropertyAnimation *Animation3 = new QPropertyAnimation(yesOpacity, "opacity");
    Animation3->setDuration(1000);
    Animation3->setStartValue(0);
    Animation3->setEndValue(1);

    QSequentialAnimationGroup *Group = new QSequentialAnimationGroup(this);
    Group->addAnimation(Animation1);
    Group->addPause(500);
    Group->addAnimation(Animation2);
    Group->addPause(500);
    Group->addAnimation(Animation3);
    Group->start();
    cupPopup->show();
    congrat->show();
    paper->show();
    yes->show();

    connect(yes, &QPushButton::clicked, this, [=]{
        ChooseScene *c=new ChooseScene;
        this->close();
        c->show();
    });
}

