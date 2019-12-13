#include "map.h"

#include "monster.h"
#include "tower.h"

Map::Map(int road[][2], int roadlength, int x, int y, int hairblood)
{
	intMonsterNumbers = 0;
	intTowerNumbers = 0;
	intHairBlood = hairblood;
	sizex = x;
	sizey = y;
	roadCellAmount = roadlength;
	MapState = new int* [x];

	for (int i = 0; i < roadlength; i++)
		for (int j = 0; j < 2; j++)
			roadLocation[i][j] = road[i][j];

	for (int i = 0; i < y; i++)
		MapState[i] = new int[y];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			MapState[i][j] = 0;
	for (int i = 0; i < roadlength - 1; i++)
		MapState[roadLocation[i][0]][roadLocation[i][1]] = -1;
	MapState[roadLocation[roadlength - 1][0]][roadLocation[roadlength - 1][1]] = -2;
}

void Map::ProduceMonster(int MonsterType = 0)
{
	monsterExisted[intMonsterNumbers] = new Monster(MonsterType, this); //0�Ź� 100 1
	intMonsterNumbers++;
}

bool Map::ProduceTower(int TowerType, int x, int y)
{
	switch (TowerType)
	{
	case 0:
		towerExisted[intTowerNumbers] = new Tower(0, x, y); //0����
		if (MapisOccupied(x, y, towerExisted[intTowerNumbers]->arraySize[0], towerExisted[intTowerNumbers]->arraySize[1]) == true)//δ��ռ�� ���Խ���
		{
			MapStateChange(x, y, towerExisted[intTowerNumbers]->arraySize[0], towerExisted[intTowerNumbers]->arraySize[1], 1);//�޸�MapState
			intTowerNumbers++;
			return true;
		}
		else
		{
			delete towerExisted[intTowerNumbers];
			towerExisted[intTowerNumbers] = nullptr;
			return false;
		}
		break;

	default:
		break;
	}
}

bool Map::MapisOccupied(int x, int y, int towersizex, int towersizey)
{
	for (int i = 0; i < towersizex; i++)
		for (int j = 0; j < towersizey; j++)
			if (MapState[i + x][j + y] != 0 || MapState[i + x][j + y] != 2)
				return false;
	return true;//δ��ռ��
}

void Map::MapStateChange(int x, int y, int towersizex, int towersizey, int newstate)
{
	for (int i = 0; i < towersizex; i++)
		for (int j = 0; j < towersizey; j++)
			MapState[i + x][j + y] = newstate;
}
bool Map::Update(int time)//time�ĵ�λ��ms
{
	for (int i = 0; i < intMonsterNumbers; i++)//���й����ƶ�
	{
		DistanceToFinal[i] = monsterExisted[i]->move();
		if (monsterExisted[i]->hitHome() == true)
		{
			intHairBlood--;
			delete monsterExisted[i];
			monsterExisted[i] = nullptr;
			for (int j = i; j < intMonsterNumbers - 1; j++)
				monsterExisted[j] = monsterExisted[j + 1];
			intMonsterNumbers--;
			if (intHairBlood == 0)
				return false;
		}
	}
	for (int i = 0; i < intTowerNumbers; i++)//����������
		towerExisted[i]->update(time, this);


	int newintMonsterNumbers = 0;
	for (int i = 0; i < intMonsterNumbers; i++)//�жϹ����Ƿ����� ������delete ͬʱά��
	{
		if (monsterExisted[i]->intHitPoint <= 0)
		{
			delete monsterExisted[i];
			monsterExisted[i] = nullptr;
		}
		else
		{
			monsterExisted[newintMonsterNumbers] = monsterExisted[i];
			newintMonsterNumbers++;
		}
	}
	intMonsterNumbers = newintMonsterNumbers;
	return true;
}