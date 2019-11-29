#include <iostream>
using namespace std;
/*需要Map提供的变量
Map.roadAmount; //道路格子的总个数
*/

class Monster{
public:
    int intHitPoint;//怪物的血量
	double monsterMoveSpeed;//怪物的速度(每次刷新走过的距离与一个格子长度的比值)
    double locationOrder;//怪物的位置，以道路格子为单位，如怪物在第三个格子的1/3位置，则值为2.333333333
    Monster(int blood, double speed);//构造函数
    double move();//怪物前进一次，并且返回与终点的距离，以道路格子为单位，同locationOrder
    bool hitHome();//判断怪物是否到老家
};

Monster::Monster(int blood, double speed) {
    intHitPoint = blood;
    monsterMoveSpeed = speed;
    locationOrder = 0;
}

double Monster::move() {
    locationOrder += monsterMoveSpeed;
    return Map.roadAmount - locationOrder;
}

bool Monster::hitHome() {
    return (locationOrder >= Map.roadAmount);
}


