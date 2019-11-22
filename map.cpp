#include "map.h"

Map::Map(int roadLocation[][2],int roadlength, int x=50,int y=30)
{
    intMonsterNumbers = 0;
    intTowerNumbers = 0;
    sizex = x;
    sizey = y;
    MapState = new int*[x];

    for(int i = 0; i < y; i++)
        MapState[i] = new int[y];

    for (int i=0;i<x;i++)
          for (int j=0;j<y;j++)
                MapState[i][j] = 0;
    for (int i=0;i<roadlength;i++)
          MapState[roadLocation[i][0]][roadLocation[i][1]] = -1;
}

void Map::ProduceMonster(int MonsterType=0)
{
    switch (MonsterType)
    {
        case 0:
            monsterExisted[intMonsterNumbers]=new Monster(100,1); //0号怪 100 1
            break;

        default:
            break;
    }
    intMonsterNumbers++;
}

bool Map::ProduceTower(int TowerType, int x, int y)
{
    switch (TowerType)
    {
        case 0:
            towerExisted[intTowerNumbers]=new Tower0(x,y); //0号塔
            if (MapisOccupied(x,y,towerExisted[intTowerNumbers]->arraySize[0],towerExisted[intTowerNumbers]->arraySize[1])==0)//未被占用 可以建塔
            {
                intTowerNumbers++;
                MapStateChange(x,y,towerExisted[intTowerNumbers]->arraySize[0],towerExisted[intTowerNumbers]->arraySize[1],'t');//修改MapState
                return true;
            }
            else
            {
                delete towerExisted[intTowerNumbers];
                return false;
            }
            break;

        default:
            break;
    }
}

bool Map::MapisOccupied(int x,int y,int towersizex,int towersizey)
{
    for (int i=0;i<towersizex;i++)
        for (int j=0;j<towersizey;j++)
            if (MapState[i+x][j+y]!='b')
                return false;
    return true;
}

void Map::MapStateChange(int x,int y,int towersizex,int towersizey,char newstate)
{
    for (int i=0;i<towersizex;i++)
        for (int j=0;j<towersizey;j++)
            MapState[i+x][j+y]=newstate;
}
void Map::Update(int time)//time的单位是ms
{
    for (int i = 0; i<intMonsterNumbers; i++)//所有怪物移动
        DistanceToFinal[i] = monsterExisted[i]->move();
    for (int i=0 ; i<intTowerNumbers; i++)//所有塔攻击
        towerExisted[i]->update(time,this);

    int newintMonsterNumbers = 0;
    for (int i=0; i<intMonsterNumbers; i++)//判断怪物是否死亡 死亡则delete 同时维护
    {
        if (monsterExisted[i]->intHitPoint <= 0)
        {
            delete monsterExisted[i];
            monsterExisted[i] = nullptr;
        }
        else
        {
            monsterExisted[newintMonsterNumbers] = monsterExisted[i];
            newintMonsterNumbers++;
        }
    }
    intMonsterNumbers = newintMonsterNumbers;
}
