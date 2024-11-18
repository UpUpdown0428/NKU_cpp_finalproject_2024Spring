#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include "chapter2scene.h"
#include <QTimer>

namespace Ui {
class Chapter2;
}

class Chapter2 : public QWidget
{
    Q_OBJECT

public:
    explicit Chapter2(QWidget *parent = nullptr);
    ~Chapter2();

private slots:
    void on_Back_clicked();
    void GameTimeEvent();//计时器回调


private:
    Ui::Chapter2 *ui;
    Chapter2Scene *scene;
    QTimer *gameTimer;
};

#endif // CHAPTER2_H
