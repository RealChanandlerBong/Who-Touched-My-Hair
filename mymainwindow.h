#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "map.h"
#include "monster.h"
#include "tower.h"
#include <QTime>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class myMainWindow; }
QT_END_NAMESPACE

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myMainWindow(QWidget *parent = nullptr);
    ~myMainWindow();

    int gameState;  //用于标记游戏进行的状态，
                             //0表示刚打开窗口，游戏未初始化，
                             //1表示处于选择角色界面
                             //2表示处于游戏进行界面
                             //3表示处于游戏暂停
                             //4表示处于游戏结束

    int roleChoose; //用于表示玩家身份，0表示玩家扮演塔，1表示玩家扮演怪

    //int originX, originY; //用于记录鼠标点击的位置，主要用于造塔时拖动用

    int towerType; //用于表示造塔的种类

    //Map myMap; 要不直接写进去，map类也作为monster和tower类的成员共用
    
    int mouseState;//标记游戏界面中鼠标的状态，1表示点击了商店的塔待建塔，0表示空闲，初始为0；

    int precellx, precelly;//上一时刻鼠标所在格子坐标

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void QPaintEvent(QPaintEvent *);

    void initial(); //根据玩家身份选择，初始化游戏界面

    void chooseRole(); //选择角色函数，隐藏/显示相关widget

    void gameStart(); //选择完角色，游戏开始

	void update();//每五秒生成新的怪+每秒检查游戏是否失败

    void produceHint(QMouseEvent *); //判断鼠标是否悬浮在某个格子上方

    QRect recTower, recMonster; //选择角色时用的按钮

    QRect recMap; //全地图

    int LatticeLength, LatticeWidth; //以像素点为单位


private slots:
    void on_actionHelp_triggered();

    void on_actionExit_triggered();

    void on_actionStart_triggered();

private:
    Ui::myMainWindow *ui;
	QTimer* fTimer; //定时器
	QTime fTimeCounter;//计时器
};
#endif // MYMAINWINDOW_H
