#ifndef TOWER_H
#define TOWER_H

#include "monster.h"

// 简单版塔类
class Tower
{
public:
    Tower(double x, double y, double w, double h, double wr, double hr, double bw, double bh, double bwr, double bhr, const char * tower, const char * bullet) {
        arrayLocation[0] = x;
        arrayLocation[1] = y;
        doubleWidth = w;
        doubleHeight =h;
        doubleWidthRef = wr;
        doubleHeightRef = hr;

        doubleBullet = 1.1;
        doubleBulWidth = bw;
        doubleBulHeight = bh;
        doubleBulWidthRef = bwr;
        doubleBulHeightRef = bhr;

        intMonsterChosen = -1;
        strTower = tower;
        strBullet = bullet;
    }
    // 模拟塔找怪
    int search(std::vector<Monster *> vecMonster) {
        double min_dist = 9999;
        double dist = 0;
        intMonsterChosen = -1;
        for (int i = 0; i < vecMonster.size(); i++) {
            dist = (arrayLocation[0] - vecMonster[i]->xMonPost)*(arrayLocation[0] - vecMonster[i]->xMonPost) +
                   (arrayLocation[1] - vecMonster[i]->yMonPost)*(arrayLocation[1] - vecMonster[i]->yMonPost);
            if (dist < min_dist && dist < 5) {
                min_dist = dist;
                intMonsterChosen = i;
            }
        }
        return intMonsterChosen;
    }
    // 模拟塔攻击
    void attack(Monster * monster) {
        monster->intHitPoint -= 1;
    }
    int arrayLocation[2];
    // 需要的参数
    double doubleWidth, doubleHeight;        // 塔的宽/高，用于贴图，随塔种类变化
    double doubleWidthRef, doubleHeightRef;  // 坐标修正量
    double doubleBulWidth, doubleBulHeight;  // 子弹的宽高
    double doubleBulWidthRef, doubleBulHeightRef; // 坐标修正量
    double doubleBullet;         // 用于子弹贴图，只需初始化为1.1
    int intMonsterChosen;        // 攻击对象在向量中的序号，无对象时设为-1
    const char * strTower;       // 图片路径(塔）
    const char * strBullet;      // 图片路径(子弹)
};

#endif // TOWER_H
