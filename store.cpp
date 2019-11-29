#include "store.h"
#include "tower.h"

store::store(QPoint store, int sX, int sY, QPoint tower, int inter, int tX, int tY, int avaNum)
{
    store = store;
    storeX = sX; storeY = sY;
    towerUL = tower;
    interval = inter;
    towerX = tX; towerY = tY;
    avaTowerNum = avaNum;
    avaTower = new Tower[ avaTowerNum ];
}

Tower* store::buyTower(QPoint mouse)
{
    for (int i = 0; i < avaTowerNum; i++)
    {
        //计算第i个塔左上角位置
        int iTowerX = towerUL.x() + i * (interval + towerX);
        int iTowerY = towerUL.y();
        //判断是否在第i个塔范围内
        if ( (mouse.x() > iTowerX) && (mouse.x() < iTowerX + towerX) && (mouse.y() > iTowerY) 
        && (mouse.y() < iTowerY + towerY)
        {
            return &(avaTower[i]);
        }
    }
}

bool store::isAfford(Tower* buy, int gold)
{
    if (buy->intCost > gold)
    {
        return 0;
    }
    return 1;
}

store::~store()
{
    delete[] avaTower;
}