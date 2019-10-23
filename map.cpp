#include "monster.cpp"
#include "tower.cpp"
class Map{
public:
    double DistanceToFinal[100];//怪物到终点的距离/-怪物威胁度
    Monster* monsterExisted[100];//地图上存在的怪物
    int intMonsterNumbers;
    Tower* towerExisted[100];//地图上存在的怪物
    int intTowerNumbers;
    int sizex,sizey;
    char **MapState; //r 路 b 空  t 塔 
    
    Map(int x=50,int y=30,int roadLocation[][2],int roadlength)
	{
		intMonsterNumbers=0;
		intTowerNumbers=0;
		sizex=x;
		sizey=y;
		MapState= new MapState[x][y];
		for (int i=0;i<x;i++)
			for (int j=0;j<y;j++)
				MapState[i][j]='b'; 
		for (int i=0;i<roadlength;i++)
			MapState[roadLocation[i][0]][roadLocation[i][1]];
	}
    
    void ProduceMonster(int MonsterType=0);
    bool ProduceTower(int TowerType=0,int x,int y);//x y 表示塔左上角坐标 
    bool MapisOccupied(int x,int y,int towersizex,int towersizey);
    void MapStateChangeToTower(int x,int y,int towersizex,int towersizey,char newstate);//修改MapState为塔 
    void Update();//time表示当前的时间，单位毫秒，该函数被timer调用，用以更新塔的攻击CD及血量
    
    
};

void Map::ProduceMonster(int MonsterType=0)
{
	switch (MonsterType)
	{
		case 0:
			monsterExisted[intMonsterNumbers]=new Monster(100,1);//0号怪 100 1
			break;
		
		default:
			break; 
	}
	intMonsterNumbers++;
}

bool Map::ProduceTower(int TowerType=0,int x,int y)
{
	switch (TowerType)
	{
		case 0:
			towerExisted[intTowerNumbers]=new Tower0(x,y);//0号塔 
			if (MapisOccupied(x,y,towerExisted[intTowerNumbers]->arraySize[0],towerExisted[intTowerNumbers]->arraySize[1])==0)//未被占用 可以建塔 
			{
				intTowerNumbers++;
				MapStateChangeToTower(x,y,towerExisted[intTowerNumbers]->arraySize[0],towerExisted[intTowerNumbers]->arraySize[1],'t');//修改MapState 
				return true;
			}	
			else
			{
				delete towerExisted[intTowerNumbers];
				return false;
			}
			break;
		
		default:
			break; 
	}

}

bool Map::MapisOccupied(int x,int y,int towersizex,int towersizey)
{
	for (int i=0;i<towersizex;i++)
		for (int j=0;j<towersizey;j++)
			if (MapState[i+x][j+y]!='b')
				return false;
	return true;
}

void Map::MapStateChange(int x,int y,int towersizex,int towersizey,char newstate)
{
	for (int i=0;i<towersizex;i++)
		for (int j=0;j<towersizey;j++)
			MapState[i+x][j+y]=newstate;
}

void Map::Update(int time)//time的单位是ms 
{
	for (int i=0;i<intMonsterNumbers;i++)//所有怪物移动 
		DistanceToFinal[i]=monsterExisted[i]->move();
	for (int i=0;i<intTowerNumbers;i++)//所有塔攻击 
		towerExisted[i]->update(time,this);
	for (int i=0;i<intMonsterNumbers;i++)//判断怪物是否死亡 死亡则delete 同时维护
	{
		int newintMonsterNumbers=0;
		if (monsterExisted[i]->intHitPoint<=0)
		{
			delete monsterExisted[i];
			monsterExisted[i]=nullptr;
		}
		else 
		{
			monsterExisted[newintMonsterNumbers]=monsterExisted[i];
			newintMonsterNumbers++;
		}	
	}
	intMonsterNumbers=newintMonsterNumbers; 
}
