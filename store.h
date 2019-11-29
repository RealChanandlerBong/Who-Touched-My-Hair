#ifndef STORE_H
#define STORE_H

#include "tower.h"

class store
{
private:
    QPoint storeUL;  //商店左上角在地图上位置
    int storeX, storeY; //商店在地图上的长宽
    QPoint towerUL; //商店内第一座塔左上角在地图上位置
    int interval;   //商店内塔之间的间隔
    int towerX, towerY; //商店内塔的长宽
    int avaTowerNum;    //商店内可用塔数目
    Tower *avaTower;  //商店内可用塔
public:
    store(QPoint store, int sX, int sY, QPoint tower, int inter, int tX, int tY, int avaNum);
    Tower* buyTower(QPoint mouse);  //判断买什么塔
    bool isAfford(Tower* buy, int gold);   //判断是否能买上
    ~store();
};

#endif