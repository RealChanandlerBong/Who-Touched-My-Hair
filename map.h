#pragma once
//#ifndef MAP_H
//#define MAP_H

class Monster;
class Tower;

class Map
{
public:

    int sizex, sizey;

    int roadCellAmount;//道路格子的总数

    int roadLocation[100][2];//按顺序排列的道路格子位置

    double DistanceToFinal[100];//怪物到终点的距离/-怪物威胁度

    int intTowerNumbers;

    int intMonsterNumbers;
    
    int intHairBlood;//头发血量 
    
    Monster* monsterExisted[100];//地图上存在的怪物

    Tower* towerExisted[100];//地图上存在的塔 

    int **MapState; //-2为头发 -1为路，0为空，1为塔，2表示可以种塔，贴一个透明的塔

    Map( int road[][2], int roadlength, int x=50, int y=30,int hairblood=10);

    void ProduceMonster(int MonsterType);

    bool ProduceTower(int TowerType,int x,int y);//x y 表示塔左上角坐标

    bool MapisOccupied(int x,int y,int towersizex,int towersizey); //指定位置的格子是否被占用

    void MapStateChange(int x,int y,int towersizex,int towersizey,int newstate);//修改MapState为塔 //就是建了一座塔

    bool Update(int);//time表示当前的时间，单位毫秒，该函数被timer调用，用以更新塔的攻击CD及血量并判断游戏是否结束，true为游戏继续 

};

//#endif // MAP_H
