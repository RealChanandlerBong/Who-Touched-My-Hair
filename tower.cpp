#include "tower.h"
#include "map.h"
#include "monster.h"

Tower::Tower(int Locationx, int Locationy, int AttackInterval,
	int Attack, int Cost, int Sizex, int Sizey,
	double AttackRadius, int HitPoint) :
	intAttackInterval(AttackInterval), intAttack(Attack),
	intCost(Cost), doubleAttackRadius(AttackRadius),
	intHitPoint(HitPoint),intTimeSum(AttackInterval){
	arrayLocation[0] = Locationx;
	arrayLocation[1] = Locationy;
	arraySize[0] = Sizex;
	arraySize[1] = Sizey;
}

Tower::Tower(int type, int Locationx, int Locationy):
intAttackInterval(typedata[type][0]), intAttack(typedata[type][1]),
intCost(typedata[type][2]), doubleAttackRadius(typedata[type][5]),
intHitPoint(typedata[type][6]), intTimeSum(typedata[type][0]){
	arrayLocation[0] = Locationx;
	arrayLocation[1] = Locationy;
	arraySize[0] = typedata[type][3];
	arraySize[1] = typedata[type][4];
}

bool Tower::update(int time, Map* map) {
	Monster* monsterDetected = searchMap(map);
	intTimeSum += time;
	if (monsterDetected && (intTimeSum >= intAttackInterval)) {
		monsterDetected->intHitPoint -= intAttack; //对怪兽进行攻击
		intTimeSum -= intAttackInterval;
	}
	if (intTimeSum > intAttackInterval) intTimeSum = intAttackInterval;
	return (intHitPoint > 0); //如果塔被摧毁，返回false,如果仍然存在，返回true
}

Monster* Tower::searchMap(Map* map) {
	Monster* monsterDetected = nullptr;
	int i = 0; //迭代器
	int intMonster = -1; //用于表示monsterDetected在map->monsterExisted中的rank
	while (i < map->intMonsterNumbers) {
		if (isInAttackingRange(map->monsterExisted[i], map)) {
			if (monsterDetected) {
				if (map->DistanceToFinal[i] < map->DistanceToFinal[intMonster]) {
					monsterDetected = map->monsterExisted[i];
					intMonster = i;
				}
			}
			else {
				monsterDetected = map->monsterExisted[i];
				intMonster = i;
			}
		}
		i++;
	} //这里用于从map里索取怪兽信息，从而判断要打哪个怪兽
	return monsterDetected;
}

bool Tower::isInAttackingRange(Monster* monster, Map* map) {
	double intDistance = (monster->monsterLocation[0] - arrayLocation[0]) *
		(monster->monsterLocation[0] - arrayLocation[0]) +
		(monster->monsterLocation[1] - arrayLocation[1]) *
		(monster->monsterLocation[1] - arrayLocation[1]);
	return(intDistance <= doubleAttackRadius* doubleAttackRadius);
}