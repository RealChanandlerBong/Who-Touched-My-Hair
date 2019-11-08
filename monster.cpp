#include "monster.h"

Monster::Monster(int blood, int speed)
{
    intHitPoint = blood;
    monsterMoveSpeed = speed;
    *arrayLocation = *roadLocation[0];
}

void Monster::move(){
    locationOrder += monsterMoveSpeed;
    *arrayLocation = *roadLocation[locationOrder];
}
/*
请求重写move函数
1 position应该是double类型，不然跳格子
2 希望能提供move后所处 roadLocation 的 rank(double类型)
*/

bool Monster::hitHome(){
    return locationOrder==roadCellAmount-1;
}
