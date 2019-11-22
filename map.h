#ifndef MAP_H
#define MAP_H

#include "monster.h"
#include "tower.h"

class Map
{
public:

    int sizex, sizey;

    int roadCellAmount;//道路格子的总数

    int roadLocation[100][2];//按顺序排列的道路格子位置

    double DistanceToFinal[100];//怪物到终点的距离/-怪物威胁度

    int intTowerNumbers;

    int intMonsterNumbers;

    Tower* towerExisted[100];//地图上存在的怪物

    Monster* monsterExisted[100];//地图上存在的怪物

    int **MapState; //-1为路，0为空，1为塔，2表示可以种塔，贴一个透明的塔

    Map( int roadLocation[][2], int roadlength, int x, int y);

    void ProduceMonster(int MonsterType);

    bool ProduceTower(int TowerType,int x,int y);//x y 表示塔左上角坐标

    bool MapisOccupied(int x,int y,int towersizex,int towersizey); //指定位置的格子是否被占用

    void MapStateChange(int x,int y,int towersizex,int towersizey,char newstate);//修改MapState为塔 //就是建了一座塔

    void Update(int);//time表示当前的时间，单位毫秒，该函数被timer调用，用以更新塔的攻击CD及血量

};

#endif // MAP_H
