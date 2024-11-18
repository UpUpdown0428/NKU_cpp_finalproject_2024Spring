#ifndef CHAPTER3MAZE_H
#define CHAPTER3MAZE_H

#include <QWidget>

class Chapter3Maze:public QWidget
{
    Q_OBJECT
public:
    Chapter3Maze();
    void keyPressEvent(QKeyEvent*);
private:
    QPoint currentPos;//当前方块的位置
    QRect finishRect;//终点位置
    int blockSize;//方块大小
    int mazeSize;//迷宫大小
    bool **maze;//迷宫的二维数组
    void generationMaze();
    bool isPath(int,int);//判断是否为通路
    bool isWall(int,int);//判断是否为墙
    void move(int,int);//移动
    QPoint findStartPosition();//寻找起始位置
protected:
    void paintEvent(QPaintEvent*);
};

#endif // CHAPTER3MAZE_H

