#ifndef CHAPTER1GAMEMODEL_H
#define CHAPTER1GAMEMODEL_H
#include <vector>
// -------------------------------- //
// 最大行和列数
const int MAX_ROW = 10;
const int MAX_COL = 15;
// 游戏可玩图片数量
const int MAX_ICON = 15;
// 游戏状态
enum GameStatus
{
    PLAYING,
    PAUSE,
    WIN,
    OVER
};
//游戏图标个数
const int kIconNum = MAX_ROW * MAX_COL *0.7;
struct PaintPoint
{
    PaintPoint(int _x, int _y) : x(_x), y (_y) {}
    int x;
    int y;
};

// -------------------------------- //

class Chapter1GameModel
{
public:
    Chapter1GameModel();
    virtual ~Chapter1GameModel();

    void startGame(); // 开始游戏
    int *getGameMap();    // 获得地图
    GameStatus checkGameStatus(); // 判断获得游戏状态，是否输赢
    bool linkTwoTiles(int srcX, int srcY, int dstX,int dstY); // 连接起点和终点方块，连接是否成功
    bool isFrozen(); // 判断是否已经成为了僵局
    bool isWin(); // 检查游戏是否结束
    int *getHint(); // 获得提示
    std::vector<PaintPoint> paintPoint; // 用于绘制的点
    // 游戏状态
    GameStatus gameStatus;

private:
    // 游戏地图，存储方块，0表示消失，1-其他数字表示图片标号
    int *gameMap;

    // 游戏提示，存储2个点
    int *hintArray;

    // 判断起点到终点的方块是否可以连接消除
    bool isCanLink(int srcX, int srcY, int dstX, int dstY);

    bool canLinkDirectly(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithOneCorner(int srcX, int srcY, int dstX, int dstY);
    bool canLinkWithTwoCorner(int srcX, int srcY, int dstX, int dstY);

    // 提示模式还是连接模式判断
    bool isFrozenMode;
};

#endif // CHAPTER1GAMEMODEL_H
