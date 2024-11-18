#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QWidget>
#include <QObject>
#include <QPalette>
#include <QPushButton>
#include <QFile>
#include <QLabel>
#include <QPropertyAnimation>

namespace Ui {
class ChooseScene;
}

class ChooseScene : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseScene(QWidget *parent = nullptr);
    ~ChooseScene();
    void VictorScene();
    void GameOverScene();

signals:
    void GameStart();
    void returnMapscene();



private slots:
    void on_pushButton_clicked();

    void on_chapter1_btn_clicked();

    void on_chapter2_btn_clicked();

    void on_chapter3_btn_clicked();

private:
    Ui::ChooseScene *ui;
};

#endif // CHOOSESCENE_H
