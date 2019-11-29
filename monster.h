//#pragma once
#ifndef MONSTER_H
#define MONSTER_H

//#include "tower.h"
//#include "map.h"

class Map;
class Monster{
public:
	Map* map;

    int intHitPoint;//�����Ѫ��

    double monsterMoveSpeed;//������ٶ�(ÿ��ˢ���߹��ľ�����һ�����ӳ��ȵı�ֵ)

    double locationOrder;//�����λ�ã��Ե�·����Ϊ��λ��������ڵ��������ӵ�1/3λ�ã���ֵΪ2.333333333

    double monsterLocation[2];

    Monster(int blood, double speed, Map *map);//���캯��

    double move();//����ǰ��һ�Σ����ҷ������յ�ľ��룬�Ե�·����Ϊ��λ��ͬlocationOrder

    bool hitHome();//�жϹ����Ƿ��ϼ�
};

#endif // MONSTER_H
