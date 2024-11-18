#ifndef RESTROOM_H
#define RESTROOM_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QTime>
#include <QLCDNumber>
/*
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QSoundEffect>
*/

namespace Ui {
class RestRoom;
}

class RestRoom : public QWidget
{
    Q_OBJECT

public:
    explicit RestRoom(QWidget *parent = nullptr);
    ~RestRoom();
    void setTheme();
    QString ChooseBackgroundColor();
    QString ChooseButtonColor();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_GRYFFINDOR_clicked();
    void on_RAVENCLAW_clicked();
    void on_SLYTHERIN_clicked();
    void on_HUFFLEPUFF_clicked();
    void on_Back_clicked();
    void StudyRoom();
    void showTime();
    void on_Back_2_clicked();

private:
    Ui::RestRoom *ui;
    QString backgroundColor;
    QString button;
    int color;
    QLCDNumber *lcd;
    QVBoxLayout *vbox;
    //QSoundEffect *bgm;
};

#endif // RESTROOM_H
