#include "restroom.h"
#include "ui_restroom.h"
#include "choosescene.h"
#include "gameintroduction.h"
#include "login.h"

enum Color{
    G,H,S,R
};

RestRoom::RestRoom(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RestRoom)
{
    ui->setupUi(this);
    //设置初始按钮颜色
    color=G;
    ui->GRYFFINDOR->setStyleSheet("background:rgb(180,4,4)");
    ui->Back->setStyleSheet("background:rgb(180,4,4);color:rgb(255, 255, 255);");
    ui->Back_2->setStyleSheet("background:rgb(180,4,4);color:rgb(255, 255, 255);");
    setTheme();

    connect(ui->pushButton_3,&QPushButton::clicked,this,&RestRoom::StudyRoom);
}

RestRoom::~RestRoom()
{
    delete ui;
}

void RestRoom::setTheme()
{
    backgroundColor=ChooseBackgroundColor();
    button=ChooseButtonColor();
    //设置休息室背景图片
    QPixmap *pix=new QPixmap(backgroundColor);
    QSize sz=ui->RestRoom_background->size();
    ui->RestRoom_background->setPixmap(pix->scaled(sz));
    //设置按钮颜色
    ui->pushButton->setStyleSheet(button);
    ui->pushButton_2->setStyleSheet(button);
    ui->pushButton_3->setStyleSheet(button);
    ui->pushButton->setFont(QFont("Harry P",20));
    ui->pushButton_2->setFont(QFont("Harry P",20));
    ui->pushButton_3->setFont(QFont("Harry P",20));
    qDebug()<<backgroundColor;

}

QString RestRoom::ChooseBackgroundColor()
{
    switch (color) {
    case 0:
        backgroundColor=":/image/RestRoom_G.jpg";
        break;
    case 1:
        backgroundColor=":/image/RestRoom_H.jpg";
        break;
    case 2:
        backgroundColor=":/image/RestRoom_S.jpg";
        break;
    case 3:
        backgroundColor=":/image/RestRoom_R.jpg";
        break;
    }
    return backgroundColor;
}

QString RestRoom::ChooseButtonColor()
{
    switch(color){
    case 0:
        button="background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                 "stop:0.0112994 rgba(180, 4, 4, 255),"
                 "stop:1 rgba(255, 255, 255, 255));"
                 "color: rgb(255, 255, 255);"
                 "border:0px groove gray;border-radius:"
                 "7px;padding:2px 4px;";
        break;
    case 1:
        button="background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                 "stop:0.0112994 rgba(255, 205, 79, 255),"
                 "stop:1 rgba(255, 255, 255, 255));"
                 "color: rgb(255, 255, 255);"
                 "border:0px groove gray;border-radius:"
                 "7px;padding:2px 4px;";
        break;
    case 2:
        button="background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                 "stop:0.0112994 rgba(53, 200, 68, 255),"
                 "stop:1 rgba(255, 255, 255, 255));"
                 "color: rgb(255, 255, 255);"
                 "border:0px groove gray;border-radius:"
                 "7px;padding:2px 4px;";
        break;
    case 3:
        button="background-color: qlineargradient(spread:pad, x1:0.52, y1:1, x2:0.54, y2:0,"
                 "stop:0.0112994 rgba(64, 145, 252, 255),"
                 "stop:1 rgba(255, 255, 255, 255));"
                 "color: rgb(255, 255, 255);"
                 "border:0px groove gray;"
                 "border-radius:7px;"
                 "padding:2px 4px;";
        break;
    }
    return button;
}

void RestRoom::on_pushButton_clicked()
{
    this->close();
    ChooseScene *c=new ChooseScene;
    c->show();

}

void RestRoom::on_pushButton_2_clicked()
{
    this->close();
    GameIntroduction *g=new GameIntroduction;
    g->mainIntoduction();
    g->show();

}

void RestRoom::on_GRYFFINDOR_clicked()
{
    color=Color::G;

    ui->GRYFFINDOR->setStyleSheet("background:rgb(180,4,4)");
    ui->Back->setStyleSheet("background:rgb(180,4,4);color: rgb(255, 255, 255);");
    ui->Back_2->setStyleSheet("background:rgb(180,4,4);color: rgb(255, 255, 255);");

    ui->HUFFLEPUFF->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    ui->SLYTHERIN->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    ui->RAVENCLAW->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                 "border-color: rgba(255, 255, 255, 0);");
    setTheme();
}
void RestRoom::on_RAVENCLAW_clicked()
{
    color=Color::R;
    ui->RAVENCLAW->setStyleSheet("background:rgb(64,145,252)");
    ui->Back->setStyleSheet("background:rgb(64,145,252);color: rgb(255, 255, 255);");
    ui->Back_2->setStyleSheet("background:rgb(64,145,252);color: rgb(255, 255, 255);");

    ui->GRYFFINDOR->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    ui->HUFFLEPUFF->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    ui->SLYTHERIN->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                 "border-color: rgba(255, 255, 255, 0);");
    setTheme();
}
void RestRoom::on_SLYTHERIN_clicked()
{
    color=Color::S;
    ui->SLYTHERIN->setStyleSheet("background:rgb(53,200,68)");
    ui->Back->setStyleSheet("background:rgb(53,200,68);color: rgb(255, 255, 255);");
    ui->Back_2->setStyleSheet("background:rgb(53,200,68);color: rgb(255, 255, 255);");
    ui->HUFFLEPUFF->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    ui->RAVENCLAW->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                 "border-color: rgba(255, 255, 255, 0);");
    ui->GRYFFINDOR->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    setTheme();
}
void RestRoom::on_HUFFLEPUFF_clicked()
{
    color=Color::H;
    ui->HUFFLEPUFF->setStyleSheet("background:rgb(255,205,79)");
    ui->Back->setStyleSheet("background:rgb(255,205,79);color: rgb(255, 255, 255);");
    ui->Back_2->setStyleSheet("background:rgb(255,205,79);color: rgb(255, 255, 255);");
    ui->SLYTHERIN->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                 "border-color: rgba(255, 255, 255, 0);");
    ui->RAVENCLAW->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                 "border-color: rgba(255, 255, 255, 0);");
    ui->GRYFFINDOR->setStyleSheet("background-color: rgba(255, 255, 255, 150);"
                                  "border-color: rgba(255, 255, 255, 0);");
    setTheme();
}


void RestRoom::on_Back_clicked()
{
    this->close();
    Login *l=new Login;
    l->show();
}

void RestRoom::StudyRoom()
{
    ui->GRYFFINDOR->close();
    ui->HUFFLEPUFF->close();
    ui->RAVENCLAW->close();
    ui->SLYTHERIN->close();
    ui->pushButton->close();
    ui->pushButton_2->close();
    ui->pushButton_3->close();
    ui->Back->close();
    ui->Back_2->raise();
    //显示时间
    vbox=new QVBoxLayout(this);
    lcd=new QLCDNumber(this);
    lcd->setFont(QFont("Times",10));
    lcd->setGeometry(200,100,450,440);
    //lcd->lower();
    showTime();
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);
    vbox->addWidget(lcd);
    vbox->addWidget(ui->Back_2);
    //背景音乐
    /*
    bgm = new QSoundEffect(this);
    bgm->setSource(QUrl::fromLocalFile(":/music/y1349.wav"));
    bgm->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    bgm->setVolume(0.5f);  //设置音量，在0到1之间
    bgm->play();
    */

}


void RestRoom::showTime()
{
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm");
    if ((time.second()%2)==0){
        text[2]=' ';
    }
    lcd->display(text);
}


void RestRoom::on_Back_2_clicked()
{
    ui->GRYFFINDOR->show();
    ui->HUFFLEPUFF->show();
    ui->RAVENCLAW->show();
    ui->SLYTHERIN->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->Back->show();
    delete lcd;
    delete ui->Back_2;
    qDebug()<<"ckicked back_2";

}

