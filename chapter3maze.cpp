#include "chapter3maze.h"
#define WALL false
#define PATH true

#include <QPainter>
#include <cstdlib>
#include <Qtime>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopServices>
#include <QMessageBox>

Chapter3Maze::Chapter3Maze() {
    //setFixedSize(600,600);
    blockSize=25;
    mazeSize=20;
    generationMaze();
    currentPos=findStartPosition();
    finishRect=QRect(QPoint(blockSize*(mazeSize-2),blockSize*(mazeSize-2)),
                       QSize(blockSize,blockSize));//设置终点坐标
}

void Chapter3Maze::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        move(0,-1);
        break;
    case Qt::Key_A:
        move(-1,0);
        break;
    case Qt::Key_S:
        move(0,1);
        break;
    case Qt::Key_D:
        move(1,0);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Chapter3Maze::generationMaze()
{
    //初始化迷宫数组
    maze=new bool*[mazeSize];
    for (int i=0;i<mazeSize;++i){
        maze[i]=new bool[mazeSize];
    }
    for (int y=0;y<mazeSize;++y){
        for (int x=0;x<mazeSize;++x){
            maze[x][y]=WALL;
        }
    }
    //随机生成迷宫
    std::srand(std::time(0));
    int xStart=std::rand()%mazeSize;
    int yStart=std::rand()%mazeSize;
    //int xStart=5;//起始x坐标
    //int yStart=5;//起始y坐标
    maze[xStart][yStart]=PATH;
    std::vector<std::pair<int,int>> cells;
    cells.push_back(std::make_pair(xStart,yStart));
    while (!cells.empty()){
        int idx=std::rand()%cells.size();//任选一个格子
        int x=cells[idx].first;
        int y=cells[idx].second;
        cells.erase(cells.begin()+idx);//从队列中删除
        std::vector<std::pair<int,int>> neighbors;
        if ((x>0)&&(!isPath(x-1,y))){
            neighbors.push_back(std::make_pair(x-1,y));
        }
        if ((y>0)&&(!isPath(x,y-1))){
            neighbors.push_back(std::make_pair(x,y-1));
        }
        if ((x<mazeSize-1)&&(!isPath(x+1,y))){
            neighbors.push_back(std::make_pair(x,y+1));
        }
        if ((y<mazeSize-1)&&(!isPath(x,y+1))){
            neighbors.push_back(std::make_pair(x,y+1));
        }
        if (!neighbors.empty()){
            cells.push_back(std::make_pair(x,y));
            //int ridx=2;
            int ridx=std::rand()%neighbors.size();
            int nx=neighbors[ridx].first;
            int ny=neighbors[ridx].second;
            if (nx>x){
                maze[x+1][y]=PATH;
            }else if(nx<x){
                maze[x-1][y]=PATH;
            }else if (ny>y){
                maze[x][y+1]=PATH;
            }else if (ny<y){
                maze[x][y-1]=PATH;
            }
            maze[nx][ny]=PATH;
            cells.push_back(std::make_pair(nx,ny));
        }
    }
    for (int i=0;i<mazeSize;++i){
        delete[] maze[i];
    }
    delete[] maze;
}

bool Chapter3Maze::isPath(int x, int y)
{
    if (x<0||x>=mazeSize||y<0||y>mazeSize){
        return false;
    }
    return maze[x][y]==PATH;
}

bool Chapter3Maze::isWall(int x, int y)
{
    if (x<0||x>=mazeSize||y<0||y>mazeSize){
        return true;
    }
    return maze[x][y]==WALL;
}

void Chapter3Maze::move(int dx, int dy)
{
    int x=currentPos.x()+dx;
    int y=currentPos.y()+dy;
    if ((x<0)||(x>=mazeSize)||(y<0)||(y>=mazeSize)||maze[x][y]==WALL){
        return;
    }
    currentPos=QPoint(x,y);
    repaint();
    if (x==mazeSize-2&&y==mazeSize-2){
        QMessageBox::information(this,"You win","COngratulations,you win the award!");
    }
}


QPoint Chapter3Maze::findStartPosition()
{
    for (int x=0;x<mazeSize;++x){
        for (int y=0;y<mazeSize;++y){
            if (maze[x][y]==PATH&&(x!=mazeSize-1||y!=mazeSize)){
                return QPoint(x,y);
            }
        }
    }
    return QPoint(0,0);
}

void Chapter3Maze::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(20,20);
    //绘制迷宫格子
    for (int y=0;y<mazeSize;++y){
        for (int x=0;x<mazeSize;++x){
            QRectF r(x*blockSize,y*blockSize,blockSize,blockSize);
            if ((x==mazeSize-2)&&(y=-mazeSize-2)){
                maze[x][y]=1;
                painter.fillRect(r,Qt::green);
            }else if (maze[x][y]==WALL){
                painter.fillRect(r,QColorConstants::Svg::darkgreen);
            }else{
                painter.fillRect(r,Qt::green);
            }
        }
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0,245,255));
    painter.drawRect(finishRect);//绘制终点矩形
    //绘制方块
    painter.setBrush(QColor(255,0,0));
    painter.setPen(Qt::black);
    painter.drawEllipse(currentPos.x()*blockSize+blockSize/4,
                        currentPos.y()*blockSize+blockSize/4,
                        blockSize/2,blockSize/2);
}

