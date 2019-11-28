#include "tower.h"
#include "map.h"
#include "monster.h"

Tower::Tower()
{

}

bool Tower::update(int time,Map* map){
    Monster* monsterDetected = searchMap(map);
    if (monsterDetected&&(time-intTimeOfLastAttack>=intAttackInterval)){
         monsterDetected->intHitPoint-=intAttack; //对怪兽进行攻击
        intTimeOfLastAttack=time;
    }
    return (intHitPoint>0); //如果塔被摧毁，返回false,如果仍然存在，返回true
}

Monster* Tower::searchMap(Map* map){
    Monster* monsterDetected=nullptr;
    int i=0; //迭代器
    int intMonster=-1; //用于表示monsterDetected在map->monsterExisted中的rank
    while(i<map->intMonsterNumbers){
        if(isInAttackingRange(map->monsterExisted[i],map)){
            if(monsterDetected){
                if(map->DistanceToFinal[i] < map->DistanceToFinal[intMonster]){
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

bool Tower::isInAttackingRange(Monster* monster,Map* map){
	double monsterx, monstery;
	monsterx = (map->roadLocation[(int)(monster->locationOrder)][0]) * ((int)(monster->locationOrder)+1- monster->locationOrder) + (map->roadLocation[1 + (int)(monster->locationOrder)][0])*(monster->locationOrder -(int)(monster->locationOrder));
	monstery = (map->roadLocation[(int)(monster->locationOrder)][1]) * ((int)(monster->locationOrder) + 1 - monster->locationOrder) + (map->roadLocation[1 + (int)(monster->locationOrder)][1]) * (monster->locationOrder - (int)(monster->locationOrder));
	double intDistance=(monsterx -arrayLocation[0])*
            (monsterx -arrayLocation[0])+
            (monstery -arrayLocation[1])*
            (monstery -arrayLocation[1]);
    return(intDistance<=doubleAttackRadius);
}
