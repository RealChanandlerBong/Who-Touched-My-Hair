#include "monster.h"
/*��ҪMap�ṩ�ı���
Map.roadAmount; //��·���ӵ��ܸ���
*/
#include"map.h"
#include "tower.h"

Monster::Monster(int blood, double speed, Map *thismap) {
    intHitPoint = blood;
    monsterMoveSpeed = speed;
	map = thismap;
    locationOrder = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    monsterLocation[0] = (map->roadLocation[(int)(locationOrder)][0]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][0]) * (locationOrder - (int)(locationOrder));
	monsterLocation[1] = (map->roadLocation[(int)(locationOrder)][1]) * ((int)(locationOrder) + 1 - locationOrder) + (map->roadLocation[1 + (int)(locationOrder)][1]) * (locationOrder - (int)(locationOrder));
    return (double(map->roadCellAmount) - locationOrder); //�����ô���£�
}

bool Monster::hitHome() {
    return (locationOrder >= map->roadCellAmount);
}

