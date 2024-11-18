#include "chapter1gamemodel.h"
#include <QString>
#include <QTime>

Chapter1GameModel::Chapter1GameModel() :gameStatus(PLAYING){

}

Chapter1GameModel::~Chapter1GameModel()
{
    if(gameMap)
    {
        free(gameMap);
        free(hintArray);
        gameMap = NULL;
    }
}

void Chapter1GameModel::startGame()
{
    //初始化数组gameMap和hintArray
    gameMap=new int[MAX_ROW * MAX_COL];//用一个数组储存方块对应的数字（图片编号1-15），初始化为0
    for(int i=0;i<MAX_ROW * MAX_COL;i++)
        gameMap[i]=0;

    hintArray = (int *)malloc(sizeof(int) * 4);//用一个含有四个元素的数组储存提示的信息（x1,x2,y1,y2），初始化为-1
    memset(hintArray, 0, 4);
    for (int i = 0; i < 4; i++)
        hintArray[i] = -1;

    /*std::vector<int> gameMap(MAX_ROW * MAX_COL, 0);
    for (int i = 0; i < MAX_ROW * MAX_COL; i++) {
        gameMap[i] = 0;
        //qDebug()<<gameMap[i];
    }
    std::vector<int> hintArray(4, -1);//共两个点
    */

    gameStatus=PLAYING;

    //填充方块标号
    //MAX_ICON是15，最大的图片数量
    int iconID=0;
    for (int i=0;i<kIconNum;i+=2){
        //每次填充连着两个（保证每个图片总有对应的图片），图片用尽后循环
        gameMap[i]=iconID%MAX_ICON+1;
        gameMap[i+1]=iconID%MAX_ICON+1;
        iconID++;
        //qDebug()<<gameMap[i];输出的全部都是远超15的数
    }
    //打乱方块
    srand((unsigned)time(0));
    for (int i=0;i<MAX_COL*MAX_ROW;i++){
        int randomID=rand()%(MAX_COL*MAX_ROW);
        std::swap(gameMap[i],gameMap[randomID]);
        qDebug()<<gameMap[i];
    }
    //初始化判断模式
    isFrozenMode=false;
    //初始化绘制点
    paintPoint.clear();
}

//得到该方块的位置
int *Chapter1GameModel::getGameMap()
{
    return gameMap;
}

//表示是否连接成功，若成功则清空获得的两方块坐标
bool Chapter1GameModel::linkTwoTiles(int srcX, int srcY, int dstX, int dstY)
{
    //成功连接就返回true反之false
    if(isCanLink(srcX,srcY,dstX,dstY)){
        //重置
        gameMap[MAX_COL*srcY+srcX]=0;
        gameMap[MAX_COL*dstY+dstX]=0;
        return true;
    }
    return false;
}


//判断是否胜利
bool Chapter1GameModel::isWin()
{
    for (int i=0;i<MAX_ROW*MAX_COL;i++){
        if(gameMap[i]){    //如果有不为0的方块则返回false
            return false;
        }
    }
    //反之遍历所有方块均全为0，全部消除
    gameStatus=WIN;
    return true;
}

int *Chapter1GameModel::getHint()
{
    return hintArray;
}



//三种连线方式
//是否可以直接连线
bool Chapter1GameModel::canLinkDirectly(int srcX, int srcY, int dstX, int dstY)
{
    //竖线连接
    if (srcX==dstX){
        if (srcY>dstY){
            std::swap(srcY,dstY);
        }
        for (int y=srcY+1;y<dstY;y++){
            if (gameMap[MAX_COL*y+srcX]){    //若这段距离有遇到方块则不能直接连接
                return false;
            }
        }
        if(!isFrozenMode){
            //记录点和路线
            PaintPoint p1(srcX,srcY),p2(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);//append
            paintPoint.push_back(p2);
        }
    }
    return true;
    //横线连接
    if (srcY==dstY){
        if (srcX>dstX){
            std::swap(srcX,dstX);
        }
        for (int x=srcX+1;x<dstX;x++){
            if (gameMap[MAX_ROW*x+srcY]){
                return false;
            }
        }
        if(!isFrozenMode){
            PaintPoint p1(srcX,srcY),p2(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);//append
            paintPoint.push_back(p2);
        }
        return true;
    }
    return false;
}
//是否可以通过一个拐角相连
bool Chapter1GameModel::canLinkWithOneCorner(int srcX, int srcY, int dstX, int dstY)
{
    //此处为了后续讨论方便，都假设srcX<dstX，若不是则交换一下
    if(srcX>dstX){
        std::swap(srcX,dstX);
        std::swap(srcY,dstY);
    }
    //先确定拐点，再确定直线线路
    if(dstY>srcY){
        if (gameMap[srcY*MAX_COL+dstX]==0){
            //右上角
            if (canLinkDirectly(srcX,srcY,dstX,srcY)&&canLinkDirectly(dstX,srcY,dstX,dstY)){
                //只有连接模式才需要记录点
                if (!isFrozenMode){
                    PaintPoint p1(srcX,srcY),p2(dstX,srcY),p3(dstX,dstY);
                    paintPoint.clear();
                    paintPoint.push_back(p1);
                    paintPoint.push_back(p2);
                    paintPoint.push_back(p3);
                }
                return true; //如果两两可以直线相连，则可以通过右上拐角相连
            }
        }
        if(gameMap[dstY*MAX_COL+srcX]==0){
            //左下角
            if (canLinkDirectly(srcX,srcY,srcX,dstY)&&canLinkDirectly(srcX,dstY,dstX,dstY)){
                if (!isFrozenMode){
                    PaintPoint p1(srcX,srcY),p2(srcX,dstY),p3(dstX,dstY);
                    paintPoint.clear();
                    paintPoint.push_back(p1);
                    paintPoint.push_back(p2);
                    paintPoint.push_back(p3);
                }
                return true;
            }
        }
    }else{
        if (gameMap[dstY*MAX_COL+srcX]==0){
            //左上角
            if (canLinkDirectly(srcX,srcY,srcX,dstY)&&canLinkDirectly(srcX,dstY,dstX,dstY)){
                if (!isFrozenMode){
                    PaintPoint p1(srcX,srcY),p2(srcX,dstY),p3(dstX,dstY);
                    paintPoint.clear();
                    paintPoint.push_back(p1);
                    paintPoint.push_back(p2);
                    paintPoint.push_back(p3);
                }
                return true;
            }
        }
        if (gameMap[srcY*MAX_COL+dstX]==0){
            //右下角
            if (canLinkDirectly(srcX,srcY,dstX,srcY)&&canLinkDirectly(dstX,srcY,dstX,dstY)){
                if (!isFrozenMode){
                    PaintPoint p1(srcX,srcY),p2(dstX,srcY),p3(dstX,dstY);
                    paintPoint.clear();
                    paintPoint.push_back(p1);
                    paintPoint.push_back(p2);
                    paintPoint.push_back(p3);
                }
                return true;
            }
        }
    }
    //上述四种情况均不满足
    return false;
}
//是否可以通过两个拐角相连
bool Chapter1GameModel::canLinkWithTwoCorner(int srcX, int srcY, int dstX, int dstY)
{
    //此处为了后续讨论方便，都假设srcX<dstX，若不是则交换一下
    if (srcX>dstX){
        std::swap(srcX,dstY);
        std::swap(srcY,dstY);
    }
    //两种情况
    //1.起点和终点之间呈阶梯式
    for(int y=0;y<MAX_ROW;y++){//遍历寻找可能的y
        if (y!=srcY&&y!=dstY){
            if (gameMap[y*MAX_COL+srcX]==0&&canLinkDirectly(srcX,srcY,srcX,y)&&canLinkWithOneCorner(srcX,y,dstX,dstY)){
                if (!isFrozenMode){
                    PaintPoint p1(srcX,srcY),p2(srcX,y),p3(dstX,dstY);
                    paintPoint.clear();
                    paintPoint.push_back(p1);
                    paintPoint.push_back(p2);
                    paintPoint.push_back(p3);
                }
                return true;
            }
        }
    }
    for (int x=0;x<MAX_COL;x++){
        if (x!=srcX&&x!=dstX){
            if(gameMap[srcY*MAX_COL]+x==0&&canLinkDirectly(srcX,srcY,x,srcY)&&canLinkWithOneCorner(x,srcY,dstX,dstY)){
                PaintPoint p1(srcX,srcY),p2(x,srcY),p3(dstX,dstY);
                paintPoint.clear();
                paintPoint.push_back(p1);
                paintPoint.push_back(p2);
                paintPoint.push_back(p3);
            }
            return true;
        }
    }
    //2.起点从外围绕道终点
    if ((srcX==0||(gameMap[srcY*MAX_COL+0]==0&&canLinkDirectly(srcX,srcY,0,srcY)))
        &&(dstX==0||(gameMap[dstY*MAX_COL+0]==0&&canLinkDirectly(0,dstY,dstX,dstY)))){   //起点为（0，0）或起点（x,y）到（0，y）和终点(x1,y1)到（0，y1）均可以直线连接
        //从起点左边出发
        if (!isFrozenMode){
            PaintPoint p1(srcX,srcY),p2(-1,srcY),p3(-1,dstY),p4(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);
            paintPoint.push_back(p2);
            paintPoint.push_back(p3);
            paintPoint.push_back(p4);
        }
        return true;
    }
    //右
    if ((srcX==MAX_COL-1||(gameMap[srcY*MAX_COL+MAX_COL-1]==0&&canLinkDirectly(srcX,srcY,MAX_COL-1,srcY)))
        &&(dstX==MAX_COL-1||(gameMap[dstY*MAX_COL+MAX_COL-1]==0&&canLinkDirectly(MAX_COL-1,dstY,dstX,dstY)))){

        if (!isFrozenMode){
            PaintPoint p1(srcX,srcY),p2(MAX_COL,srcY),p3(MAX_COL,dstY),p4(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);
            paintPoint.push_back(p2);
            paintPoint.push_back(p3);
            paintPoint.push_back(p4);
        }
        return true;
    }
    //上
    if ((srcY==0||(gameMap[srcX*MAX_ROW+0]==0&&canLinkDirectly(srcX,srcY,srcX,0)))
        &&(dstY==0||(gameMap[dstX*MAX_ROW+0]==0&&canLinkDirectly(dstX,0,dstX,dstY)))){
        //从起点左边出发
        if (!isFrozenMode){
            PaintPoint p1(srcX,srcY),p2(srcX,-1),p3(dstX,-1),p4(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);
            paintPoint.push_back(p2);
            paintPoint.push_back(p3);
            paintPoint.push_back(p4);
        }
        return true;
    }
    //下
    if ((srcY==MAX_ROW-1||(gameMap[srcX*MAX_ROW+MAX_ROW-1]==0&&canLinkDirectly(srcX,srcY,srcX,MAX_ROW-1)))
        &&(dstY==MAX_ROW-1||(gameMap[dstX*MAX_ROW-1+MAX_ROW-1]==0&&canLinkDirectly(dstX,MAX_ROW-1,dstX,dstY)))){

        if (!isFrozenMode){
            PaintPoint p1(srcX,srcY),p2(srcX,MAX_ROW),p3(dstX,MAX_ROW),p4(dstX,dstY);
            paintPoint.clear();
            paintPoint.push_back(p1);
            paintPoint.push_back(p2);
            paintPoint.push_back(p3);
            paintPoint.push_back(p4);
        }
        return true;
    }
    return false;//如果不是以上六种情况，则无法连接
}



//判断是否僵局，并记录提示
bool Chapter1GameModel::isFrozen()
{
    for (int i = 0; i < MAX_ROW * MAX_COL - 1; i++)
        for( int j = i + 1; j < MAX_ROW * MAX_COL; j++)
        {
            int srcX = i % MAX_COL;
            int srcY = i / MAX_COL;
            int dstX = j % MAX_COL;
            int dstY = j / MAX_COL;

            // 只要能找到可以连接的就不为僵局
            isFrozenMode = true;
            if (isCanLink(srcX, srcY, dstX, dstY)){
                // 记录第一个可以连接的提示
                hintArray[0] = srcX;
                hintArray[1] = srcY;
                hintArray[2] = dstX;
                hintArray[3] = dstY;
                isFrozenMode = false;
                return false;
            }
        }
    isFrozenMode = false;
    return true;
}

//获取到点击的两个方块的坐标后，判断是否可以连线
bool Chapter1GameModel::isCanLink(int srcX, int srcY, int dstX, int dstY)
{
    //判断点击的两个方块不是同一个且不是空
    if (gameMap[srcY*MAX_COL+srcX]==0||gameMap[dstY*MAX_COL+dstX]==0){  //为空
        return false;
    }
    if (srcX==dstX&&srcY==dstY){
        return false;
    }
    if (gameMap[MAX_COL*srcY+srcX]!=gameMap[MAX_COL*dstY+dstX]){
        return false;
    }
    if (canLinkDirectly(srcX,srcY,dstX,dstY)){
        return true;
    }
    if (canLinkWithOneCorner(srcX,srcY,dstX,dstY)){
        return true;
    }
    if(canLinkWithTwoCorner(srcX,srcY,dstX,dstY)){
        return true;
    }
    return false;
}




