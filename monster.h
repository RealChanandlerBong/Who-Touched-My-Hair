#ifndef MONSTER_H
#define MONSTER_H

#include "tower.h"
#include "map.h"

class Monster
{
    friend Tower;

    friend Map;

public:
    int intHitPoint;//怪物的血量

    int arrayLocation[2];//怪物的位置

    int monsterMoveSpeed;//怪物的速度

    int locationOrder;//怪物处于第几个道路格子上

    Monster(int blood, int speed);//构造函数

    void move();//怪物前进一次

    bool hitHome();//判断怪物是否到老家
};

#endif // MONSTER_H
