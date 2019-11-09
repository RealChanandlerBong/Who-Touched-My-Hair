#include <iostream>
using namespace std;
/*需要Map提供的变量
Map.roadAmount; //沿着道路中心线的像素颗粒的总个数（实际上就是怪兽能走的位置）
int** Map.roadLocation;//按顺序排列的道路中心线颗粒坐标（按顺序排列好的）
*/
class Monster{
public:
    int roadCellAmount=1;//道路格子的总数
    int intHitPoint;//怪物的血量
    int arrayLocation[2];//怪物的位置
	int monsterMoveSpeed;//怪物的速度(每次刷新走过多少个像素)
    int locationOrder;//怪物处于第几个道路中心线像素上
    Monster(int blood, int speed){//构造函数
        intHitPoint = blood;
        monsterMoveSpeed = speed;
        *arrayLocation = *Map.roadLocation[0];
    }
    int move();//怪物前进一次，并且返回与终点的道路距离(以像素为单位)
    bool hitHome();//判断怪物是否到老家
};

int Monster::move(){
    locationOrder += monsterMoveSpeed;
    *arrayLocation = *Map.roadLocation[locationOrder];
    return Map.roadamount - locationOrder;
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