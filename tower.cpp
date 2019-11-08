#include "tower.h"

Tower::Tower()
{

}

bool Tower::update(int time,Map* map){
    Monster* monsterDetected = searchMap(map);
    if (monsterDetected&&(time-intTimeOfLastAttack>=intAttackInterval)){
         monsterDetected->intHitPoint-=intAttack;//对怪兽进行攻击
        intTimeOfLastAttack=time;
    }
    return (intHitPoint>0);//如果塔被摧毁，返回false,如果仍然存在，返回true
}

Monster* Tower::searchMap(Map* map){
    Monster* monsterDetected=nullptr;
    int i=0;//迭代器
    int intMonster=-1;//用于表示monsterDetected在map->monsterExisted中的rank
    while(i<map->intMonsterNumbers){
        if(isInAttackingRange(map->monsterExisted[i])){
            if(monsterDetected){
                if(map->doubleThreatLevel[i]>map->doubleThreatLevel[intMonster]){
                    monsterDetected=map->monsterExisted[i];
                    intMonster=i;
                }
            }
            else{
                monsterDetected=map->monsterExisted[i];
                intMonster=i;
            }
        }
    } //这里用于从map里索取怪兽信息，从而判断要打哪个怪兽
    return monsterDetected;
}

bool Tower::isInAttackingRange(Monster* monster){
    double intDistance=(monster->arrayLocation[0]-arrayLocation[0])*
            (monster->arrayLocation[0]-arrayLocation[0])+
            (monster->arrayLocation[1]-arrayLocation[1])*
            (monster->arrayLocation[1]-arrayLocation[1]);
    return(intDistance<=doubleAttackRadius);
}

class Tower0 : public Tower
{
    Tower0(int Locationx=1,int Locationy=1):Tower(Locationx,Locationy,1000,10,10,2,2,5.0,100){ }//构造函数，初始化整个塔
};
