#ifndef GAMEINTRODUCTION_H
#define GAMEINTRODUCTION_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTime>
#include <QLabel>
#include <QTimer>
#include <QPushButton>

namespace Ui {
class GameIntroduction;
}

class GameIntroduction : public QWidget
{
    Q_OBJECT

public:
    explicit GameIntroduction(QWidget *parent = nullptr);
    ~GameIntroduction();
    void Background();
    //QString characterImagePath1;
    //QString characterImagePath2;
    QString backgroundImagePath;
    void mainIntoduction();
    void Introduction1();
    void Introduction2();
    void Introduction3();

private:
    Ui::GameIntroduction *ui;
    QLabel *cupPopup;
    QPushButton *will;

private slots:
    void onButtonClick();

};
/*
class CharacterAnimation : public QWidget {
    Q_OBJECT

public:
    CharacterAnimation(QWidget *parent = nullptr) : QWidget(parent) {
        // 初始化QLabel用于显示图片
        imageLabel = new QLabel(this);
        imageLabel->setGeometry(QRect(QPoint(50, 150), QSize(200, 200))); // 设置标签位置和大小
        // 加载图片
        QPixmap pixmap1(":/image/Deng1.png");
        QPixmap pixmap2(":/image/Deng2.png");
        images.push_back(pixmap1);
        images.push_back(pixmap2);

        // 设置定时器

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CharacterAnimation::updateImage);
        timer->start(500); // 每500毫秒切换一次图片

        //currentIndex = 0;
        //imageLabel->setPixmap(images[currentIndex]);
    }
private slots:
    void updateImage(){
        currentIndex = (currentIndex + 1) % images.size(); // 循环切换图片
        imageLabel->setPixmap(images[currentIndex]);
    }
private:
    QLabel *imageLabel;
    QVector<QPixmap> images;
    int currentIndex;
};
*/



#endif // GAMEINTRODUCTION_H
