//塔需要从地图中索取怪物信息，因此需要怪物类和地图类都写好才能继续补充update函数

#include "monster.cpp"
#include "map.cpp"


class Tower{
public:
    int arrayLocation[2];//位置坐标，[0]为x，[1]为y
    int intAttackInterval;//攻击间隔，单位毫秒
    int intAttack;//攻击力
    int intCost;//价格
    int arraySize[2];//塔的大小，长乘宽，[0]为水平长度，[1]为竖直长度
    double doubleAttackRadius;//攻击范围，默认为圆形，该变量代表圆的半径
    int intHitPoint;//塔的剩余血量
    bool boolMonsterDetected;//
    int intTimeOfLastAttack;//上次攻击的时间
    Tower(int Locationx=1,int Locationy=1,int AttackInterval=1000,
          int Attack=10,int Cost=10,int Sizex=2,int Sizey=2,
          double AttackRadius=5,int HitPoint=100):
          intAttackInterval(AttackInterval),intAttack(Attack),
          intCost(Cost),doubleAttackRadius(AttackRadius),
          intHitPoint(HitPoint){
        arrayLocation[0]=Locationx;
        arrayLocation[1]=Locationy;
        arraySize[0]=Sizex;
        arraySize[1]=Sizey;
    }//构造函数，初始化整个塔
    bool update(int time,Map* map);//time表示当前的时间，单位毫秒，该函数被timer调用，用以更新塔的攻击CD及血量
    Monster* searchMap(Map* map);//从map中搜索威胁最大（最靠近终点）且在攻击范围内的怪物
    bool isInAttackingRange(Monster* monster);//判断monster是不是在塔的攻击范围内
};

bool Tower::update(int time,Map* map){
    Monster* monsterDetected=searchMap(map);
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
                if(map->monsterExisted[i]>map->monsterExisted[intMonster]){
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
