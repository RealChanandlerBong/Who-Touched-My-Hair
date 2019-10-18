#include "monster.cpp"
class Map{
public:
    int intThreatLevel[100];//怪物威胁度
    Monster* monsterExisted[100];//地图上存在的怪物
    int intMonsterNumbers;
};
