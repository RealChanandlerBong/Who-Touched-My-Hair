#include <iostream>
using namespace std;

int roadCellAmount=1;//道路格子的总数
int roadLocation[100][2]={0};//按顺序排列的道路格子位置

class Monster{
public:
    int intHitPoint;//怪物的血量
    int arrayLocation[2];//怪物的位置
	int monsterMoveSpeed;//怪物的速度
    int locationOrder;//怪物处于第几个道路格子上
    Monster(int blood, int speed){//构造函数
        intHitPoint = blood;
        monsterMoveSpeed = speed;
        *arrayLocation = *roadLocation[0];
    }
    void move();//怪物前进一次
    bool hitHome();//判断怪物是否到老家
};

void Monster::move(){
    locationOrder += monsterMoveSpeed;
    *arrayLocation = *roadLocation[locationOrder];
}

bool Monster::hitHome(){
    return locationOrder==roadCellAmount-1;
}


int main(){
    Monster m(1,1);
    m.move();
    cout<<"1111111";
    return 0;
}