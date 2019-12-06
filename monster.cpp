#include "monster.h"

#include"map.h"
#include "tower.h"

Monster::Monster(int type, Map *thismap) {
    if(type == 1) {
        intHitPoint = 10;
        monsterMoveSpeed = 1;
        doubleEarn = 2;
    }
    else if(type == 2) {
        intHitPoint = 20;
        monsterMoveSpeed = 0.5;
        doubleEarn = 5;
    }
    else {
        intHitPoint = 50;
        monsterMoveSpeed = 0.1;
        doubleEarn = 15;
    }
	map = thismap;
    locationOrder = 0;
    doubleMoveDistance = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    doubleMoveDistance += monsterMoveSpeed;
    monsterLocation[0] = (map->roadLocation[(int)(locationOrder)][0]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][0]) * (locationOrder - (int)(locationOrder));
	monsterLocation[1] = (map->roadLocation[(int)(locationOrder)][1]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][1]) * (locationOrder - (int)(locationOrder));
    return (double(map->roadCellAmount) - locationOrder); 
}

bool Monster::hitHome() {
    return (locationOrder >= map->roadCellAmount);
}

double Monster::moneyobtain() {
    return doubleEarn * doubleMoveDistance;
}
