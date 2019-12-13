#include "store.h"
#include "tower.h"
#include "qpoint.h"

store::store(QPoint store, int sX, int sY, QPoint tower, int inter, int tX, int tY, int avaNum)
{
    store = store;
    storeX = sX; storeY = sY;
    towerUL = tower;
    interval = inter;
    towerX = tX; towerY = tY;
    avaTowerNum = avaNum;
}

int store::buyTower(QPoint mouse)
{
    for (int i = 0; i < avaTowerNum; i++)
    {
        //计算第i个塔左上角位置
        int iTowerX = towerUL.x() + i * (interval + towerX);
        int iTowerY = towerUL.y();
        //判断是否在第i个塔范围内
        if ( (mouse.x() > iTowerX) && (mouse.x() < iTowerX + towerX)
            && (mouse.y() > iTowerY) && (mouse.y() < iTowerY + towerY))
            return i;
    }
    return -1;
}

bool store::isAfford(int towerType, int gold)
{
    if(towerType != -1)
    {
        Tower* towerTemp=new Tower((towerType, 0, 0));
        int r = (towerTemp->intCost > gold);
        delete towerTemp;
        return r;
    }
    else return 0;
}


store::~store() {}
