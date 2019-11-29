//#pragma once
#ifndef TOWER_H
#define TOWER_H
#include <iostream>
using namespace std;

class Map;
class Monster;

const double typedata[][7] = {
//	AttackInterval	Cost			Sizey			HitPoint
//			Attack			Sizex			AttackRadius
	500,	10,		10,		1,		1,		8.0,	100,
	300,	30,		40,		1,		1,		2.0,	100,
	800,	20,		30,		1,		1,		4.0,	200,
};

class Tower
{
public:
	Tower();

	int arrayLocation[2];//位置坐标，[0]为x，[1]为y

	int intAttackInterval;//攻击间隔，单位毫秒

	int intAttack;//攻击力

	int intCost;//价格

	int arraySize[2];//塔的大小，长乘宽，[0]为水平长度，[1]为竖直长度

	double doubleAttackRadius;//攻击范围，默认为圆形，该变量代表圆的半径

	int intHitPoint;//塔的剩余血量

	bool boolMonsterDetected;//

	int intTimeSum;//未攻击时间的累加

	Tower(int Locationx, int Locationy, int AttackInterval,	int Attack, int Cost,
		int Sizex, int Sizey,double AttackRadius, int HitPoint);//构造函数，初始化整个塔

	Tower(int type, int Locationx, int Locationy);

	bool update(int time, Map* map);//time表示当前的时间，单位毫秒，该函数被timer调用，用以更新塔的攻击CD及血量

	bool isInAttackingRange(Monster* monster, Map* map);//判断怪是否在塔的攻击范围内

	Monster* searchMap(Map* map);//从map类索取怪的信息，判断要打哪个怪
};

#endif // TOWER_H