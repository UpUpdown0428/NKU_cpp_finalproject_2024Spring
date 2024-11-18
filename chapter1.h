#ifndef CHAPTER1_H
#define CHAPTER1_H

#include <QWidget>
#include <QPushButton>
#include <QRegularExpression>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include "chapter1gamemodel.h"
#include "choosescene.h"

// --------- 全局变量 --------- //
const int kIconSize = 36;
const int kTopMargin = 70;
const int kLeftMargin = 50;

//const QString kIconReleasedStyle = " ";
//const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)";
//const QString kIconHintStyle = "background-color: rgba(255, 0, 0, 255)";

const int kGameTimeTotal = 5*60 * 1000; // 总时间
const int kGameTimerInterval = 300;
const int kLinkTimerDelay = 700;
// -------------------------- //

struct IconButton:QPushButton{//结构体“IconButton”继承自QPushButton，之后设置槽的时候会用到pressed(),hide(),show()等

public:
    IconButton(QWidget *parent=nullptr):
        QPushButton(parent),
        xID(-1),
        yID(-1)
    {}

    //IconButton中包含(xID,yID)
    int xID;
    int yID;


};

namespace Ui {
class Chapter1;
}

class Chapter1 : public QWidget
{
    Q_OBJECT

public:
    explicit Chapter1(QWidget *parent = nullptr);
    ~Chapter1();
    void initGame();
    void VictorScene();
    void GameOverScene();
private slots:
    void on_Back_clicked();
    void GameTimeEvent();//计时器回调
    void onIconButtonPressed();//icon点击时响应
    void handleLinkEffect();//消除连线
    void on_hints_clicked();//获得提示


private:
    Ui::Chapter1 *ui;
    Chapter1GameModel* game;
    IconButton *iconButton[MAX_ROW*MAX_COL];//图片button数组
    QTimer *gameTimer;
    IconButton *preIcon,*curIcon;//记录点击的icon 和 提示的icon
    bool isLinking;//维持一个连接状态的标志

};

#endif // CHAPTER1_H
