#include "chapter1.h"
#include "ui_chapter1.h"
#include "choosescene.h"
#include "gameintroduction.h"
#include <QTimer>

Chapter1::Chapter1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chapter1)
{
    ui->setupUi(this);
    //设置背景图片
    QString imagePath=":/image/PotionClass.jpg";//设置背景图片路径
    //检查图片是否存在
    if (QFile::exists(imagePath)){
        QPixmap backgroundImage(imagePath);
        if (!backgroundImage.isNull()) {
            backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);// 调整图片尺寸以适应窗口大小
            QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
            this->setPalette(palette);
        }
    }
    QPixmap *pix=new QPixmap(":/image/snp.png");
    QSize sz=ui->snp->size();
    ui->snp->setPixmap(pix->scaled(sz));
    initGame();

}

Chapter1::~Chapter1()
{
    delete ui;
}

void Chapter1::initGame(){
    //启动游戏
    game=new Chapter1GameModel;
    game->startGame();
    //添加button
    for (int i=0;i<MAX_ROW*MAX_COL;i++){
        iconButton[i]=new IconButton(this);
        iconButton[i]->setGeometry(kLeftMargin+(i%MAX_COL)*kIconSize,kTopMargin+(i/MAX_COL)*kIconSize,kIconSize,kIconSize);//(x,y,w,h)设置图标的位置
        //设置索引（表示为坐标形式）
        iconButton[i]->xID=i%MAX_COL;
        iconButton[i]->yID=i/MAX_COL;

        iconButton[i]->show();//显示图标
        qDebug()<<game->getGameMap()[i];
        if (game->getGameMap()[i]){
            //有方块就设置图片
            QPixmap iconPix;
            QString fileString = QStringLiteral(":/image/Chapter1/%1.png").arg(game->getGameMap()[i]);
            iconPix.load(fileString);
            QIcon icon(iconPix);
            iconButton[i]->setIcon(icon);
            iconButton[i]->setIconSize(QSize(kIconSize,kIconSize));
            //添加按下的信号槽
            connect(iconButton[i],SIGNAL(pressed()),this,SLOT(onIconButtonPressed()));
        }else{
            iconButton[i]->hide();
        }
    }

    //进度条
    ui->timeBar->setMaximum(kGameTimeTotal);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(kGameTimeTotal);
    ui->timeBar->setStyleSheet("QProgressBar{border-radius:5px;background:white;} QProgressBar::chunk{border-radius:5px;background:blue}");

    //游戏计时器
    gameTimer=new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(GameTimeEvent()));
    gameTimer->start(kGameTimerInterval);
    // 连接状态值
    isLinking = false;
}

void Chapter1::VictorScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“胜利图片”
    QLabel *label=new QLabel(this);
    QPixmap Origin(":/image/victory.png");
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
    victoryAnimation->start();
}

void Chapter1::GameOverScene()
{
    //获取窗口中心
    int centerX=width()/2;
    int centerY=height()/2;
    //创建QLabel以插入“游戏结束图片”
    QLabel *label=new QLabel(this);
    QPixmap Origin(":/image/GameOver.png");
    QPixmap Pixmap=Origin.scaled(Origin.size(),Qt::KeepAspectRatio);
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

void Chapter1::on_Back_clicked()
{
    this->close();
    ChooseScene *c=new ChooseScene;
    c->show();
}

void Chapter1::GameTimeEvent()
{
    //进度条效果设计
    if (ui->timeBar->value()==0){
        gameTimer->stop();
        GameOverScene();
    }else{
        ui->timeBar->setValue(ui->timeBar->value()-kGameTimerInterval);
    }
}

void Chapter1::handleLinkEffect(){
    //消除成功，隐藏掉，并析构
    game->paintPoint.clear();
    preIcon->hide();
    curIcon->hide();
    preIcon=NULL;
    curIcon=NULL;
    //重绘
    update();
    //恢复状态
    isLinking=false;
}

void Chapter1::onIconButtonPressed(){
    //如果当前有方块在连接则不能点击方块
    //记录当前点击的icon
    curIcon=dynamic_cast<IconButton *>(sender());
    if (!preIcon){
        //如果单击一个icon
        curIcon->setStyleSheet("background-color: rgba(255, 255, 12, 161)");
        preIcon=curIcon;
    }else{
        if (curIcon!=preIcon){
            //如果不是同一个button就都标记，尝试连接
            curIcon->setStyleSheet("background-color: rgba(255, 255, 12, 161)");
            if (game->linkTwoTiles(preIcon->xID,preIcon->yID,curIcon->xID,curIcon->yID)){//当可以连接
                //锁住当前状态
                isLinking=true;
                //重绘
                update();
                //延迟后实现连接效果
                QTimer::singleShot(kLinkTimerDelay,this,SLOT(handleLinkEffect()));
                //每次检查一下是否僵局
                if (game->isFrozen()&&!game->isWin()){
                    GameOverScene();
                    QMessageBox::information(this,"oops","dead game,try again");
                }
                //检查一下是否胜利
                if (game->isWin()){
                    VictorScene();
                    QMessageBox::information(this,"great!You're an intelligent wizard!","Now go to the next level with your potions!");                    
                }
                //int *hints=game->getHint();
            }else{
                //消除失败，恢复
                preIcon->setStyleSheet("");
                curIcon->setStyleSheet("");
                //指针置空，用于下一次点击判断
                preIcon=NULL;
                curIcon=NULL;
            }
        }else if(curIcon==preIcon){
            preIcon->setStyleSheet("");
            curIcon->setStyleSheet("");
            preIcon=NULL;
            curIcon=NULL;
        }
    }
}


void Chapter1::on_hints_clicked()
{
    //初始时不能获得提示
    for (int i=0;i<4;i++){
        if (game->getHint()[i]==-1){
            return;
        }
    }
    int srcX=game->getHint()[0];
    int srcY=game->getHint()[1];
    int dstX=game->getHint()[2];
    int dstY=game->getHint()[3];
    IconButton *srcIcon=iconButton[srcY*MAX_COL+srcX];
    IconButton *dstIcon=iconButton[dstY*MAX_COL+dstX];
    srcIcon->setStyleSheet("background-color: rgba(255, 0, 0, 255)");
    dstIcon->setStyleSheet("background-color: rgba(255, 0, 0, 255)");
}


