//#pragma once
#ifndef MONSTER_H
#define MONSTER_H

//#include "tower.h"
//#include "map.h"

class Map;
class Monster{
public:
	Map* map;

    int intHitPoint;

    double monsterMoveSpeed;

    double locationOrder;

    double monsterLocation[2];

    Monster(int type, Map *map);

    double move();

    bool hitHome();

    double moneyobtain();

    double doubleMoveDistance;

    double doubleEarn;
};

#endif // MONSTER_H
