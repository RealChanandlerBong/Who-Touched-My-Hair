#ifndef MONSTER_H
#define MONSTER_H

// 简化版怪物类
class Monster
{
public:
    Monster(double x, double y, double w, double h, double rw, double rh, int hp, int fp, const char * monster) {
        xMonPost = x;
        yMonPost = y;
        doubleWidth = w;
        doubleHeight =h;
        doubleWidthRef = rw;
        doubleHeightRef = rh;

        intHitPoint = hp;
        intFullPoint = fp;

        flag = 0;
        strMonster = monster;
    }
    // 模拟怪物的行动
    void move()
    {
        if (xMonPost >= 2 && xMonPost <= 2.1 && yMonPost == 4)
            flag = 1;
        if (xMonPost >= 2 && xMonPost <= 2.1 && yMonPost >= 8 && yMonPost <= 8.1)
            flag = 0;
        if (xMonPost >= 9 && xMonPost <= 9.1 && yMonPost >= 8 && yMonPost <= 8.1)
            flag = 3;
        if (xMonPost >= 9 && xMonPost <= 9.1 && yMonPost <= 5 && yMonPost >= 4.9)
            flag = 0;
        if (xMonPost >= 13 && xMonPost <= 13.1 && yMonPost <= 5 && yMonPost >= 4.9)
            flag = 1;
        if (xMonPost >= 13 && xMonPost <= 13.1 && yMonPost >= 8 && yMonPost <= 8.1)
            flag = 0;
        if (xMonPost >= 15 && xMonPost <= 15.1 && yMonPost >= 8 && yMonPost <= 8.1)
            flag = 3;
        if (xMonPost >= 15 && xMonPost <= 15.1 && yMonPost <= 2 && yMonPost >= 1.9)
            flag = -1;
        if (flag == 0)
            xMonPost += 0.05;
        if (flag == 1)
            yMonPost += 0.05;
        if (flag == 2)
            xMonPost -= 0.05;
        if (flag == 3)
            yMonPost -= 0.05;
    }
    int flag;
    int intHitPoint;
    // 需要的参数
    int intFullPoint;      // 总血量
    double xMonPost, yMonPost;   // (x, y)坐标
    double doubleWidth, doubleHeight;        // 怪物的宽/高，用于贴图，随怪物种类变化
    double doubleWidthRef, doubleHeightRef;  // 坐标修正量
    const char * strMonster;     // 图片路径(怪)
};

#endif // MONSTER_H
