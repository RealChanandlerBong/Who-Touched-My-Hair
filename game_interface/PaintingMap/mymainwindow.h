#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <vector>
#include "tower.h"
#include "monster.h"

// 贴图函数
namespace Ui {
    class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myMainWindow(QWidget *parent = 0);
    ~myMainWindow();
    void paintEvent(QPaintEvent *);
    void paintTower(QPainter *);
    void paintMonster(QPainter *);
private slots:
    void updateMap();
private:
    Ui::myMainWindow *ui;
    std::vector<Tower *> vecTower;     // 塔向量，用于塔信息
    std::vector<Monster *> vecMonster; // 怪物向量，用于存放怪物信息
    double mapWidth, mapHeight;    // 地图宽/高
    double wRatio, hRatio;         // 贴图参数
};

#endif // MYMAINWINDOW_H
