#include "monster.h"
#include "map.h"
/*需要Map提供的变量
Map.roadAmount; //道路格子的总个数
*/

Monster::Monster(int blood, double speed) {
    intHitPoint = blood;
    monsterMoveSpeed = speed;
    locationOrder = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    return (double(roadCellAmount) - locationOrder); //这边怎么回事？
}

bool Monster::hitHome() {
    return (locationOrder == Map.roadAmount + 1);
}
