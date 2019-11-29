#include "monster.h"
/*��ҪMap�ṩ�ı���
Map.roadAmount; //��·���ӵ��ܸ���
*/
#include"map.h"
#include "tower.h"

Monster::Monster(int type, Map *thismap) {
    if(type == 1) {
        intHitPoint = 10;
    monsterMoveSpeed = 1;
    }
    else if(type == 2) {
        intHitPoint = 20;
    monsterMoveSpeed = 0.5;
    }
    else {
        intHitPoint = 30;
    monsterMoveSpeed = 0.1;
    }
	map = thismap;
    locationOrder = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    monsterLocation[0] = (map->roadLocation[(int)(locationOrder)][0]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][0]) * (locationOrder - (int)(locationOrder));
	monsterLocation[1] = (map->roadLocation[(int)(locationOrder)][1]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][1]) * (locationOrder - (int)(locationOrder));
    return (double(map->roadCellAmount) - locationOrder); 
}

bool Monster::hitHome() {
    return (locationOrder >= map->roadCellAmount);
}

