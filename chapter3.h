#ifndef CHAPTER3_H
#define CHAPTER3_H

#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFile>

#include "chapter3maze.h"

namespace Ui {
class Chapter3;
}

class Chapter3 : public QWidget
{
    Q_OBJECT

public:
    explicit Chapter3(QWidget *parent = 0);
    Chapter3Maze *maze;

    ~Chapter3();
public slots:
    void GameTimeEvent();
    void VictorScene();
    void GameOverScene();
private:
    Ui::Chapter3 *ui;
    QTimer *gameTimer;

};

#endif // CHAPTER3_H
