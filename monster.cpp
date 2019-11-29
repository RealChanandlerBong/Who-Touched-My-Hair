#include "monster.h"
/*需要Map提供的变量
Map.roadAmount; //道路格子的总个数
*/
#include"map.h"

Monster::Monster(int blood, double speed, Map *thismap) {
    intHitPoint = blood;
    monsterMoveSpeed = speed;
	map = thismap;
    locationOrder = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    return (double(map->roadCellAmount) - locationOrder); //这边怎么回事？
}

bool Monster::hitHome() {
    return (locationOrder == map->roadCellAmount + 1);
}
