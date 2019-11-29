#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "qpainter.h"

myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    // 贴图参数
    mapWidth = 17;
    mapHeight = 11;
    wRatio = 60;
    hRatio = 75;
    // 生成塔、怪的样例用于测试
    Tower * towZero = new Tower(6, 7, 2.2 * wRatio, 2.2 * hRatio, 0.6, 0.15, 0.3 * wRatio, 0.3 * hRatio, -0.3, -0.3, ":/tower/pot.png", ":/bullet/pot_bullet.png");
    Tower * towFirst = new Tower(8, 7, 1.5 * wRatio, 1.5 * hRatio, 0.25, 0.25, 0.25 * wRatio, 0.25 * hRatio, 0, 0, ":/tower/ge.png", ":/bullet/ge_bullet.png");
    Tower * towSecond = new Tower(3, 7, 1.2 * wRatio, 0.8 * hRatio, 0.05, -0.1, 0.4 * wRatio, 0.25 * hRatio, -0.2, -0.1, ":/tower/water.png", ":/bullet/water_bullet.png");
    Tower * towThird = new Tower(1, 6, 1.2 * wRatio, 0.8 * hRatio, 0.1, -0.1, 0.4 * wRatio, 0.25 * hRatio, -0.2, -0.1, ":/tower/water.png", ":/bullet/water_bullet.png");
    vecTower.push_back(towZero);
    vecTower.push_back(towFirst);
    vecTower.push_back(towSecond);
    vecTower.push_back(towThird);
    Monster * monZero = new Monster(0, 4, 2 * wRatio, 1.1 * hRatio, 0.05, 0.15, 200, 200, ":/monster/homework.png");
    Monster * monFirst = new Monster(-1, 4, 2 * wRatio, 1.1 * hRatio, 0.05, 0.15, 200, 200, ":/monster/homework.png");
    Monster * monSecond = new Monster(-2, 4, 1.3 * wRatio, 1.3 * hRatio, 0.15, 0.4, 1000, 1000, ":/monster/quant.png");
    vecMonster.push_back(monZero);
    vecMonster.push_back(monFirst);
    vecMonster.push_back(monSecond);

    setWindowTitle(tr("Map"));
    resize(1020, 825);
}

myMainWindow::~myMainWindow()
{
    delete ui;
}


void myMainWindow::updateMap()
{
    // 模拟塔、怪的更新
    for (int i = 0; i < vecMonster.size(); i++)
    {
        vecMonster[i]->move();
        for (int j = 0; j < vecTower.size(); j++) {
            int order = vecTower[j]->search(vecMonster);
            if (order != -1)
                vecTower[j]->attack(vecMonster[order]);
            if (vecMonster[i]->intHitPoint <= 0 || vecMonster[i]->flag == -1) {
                vecMonster.erase(vecMonster.begin() + i);
                Monster * monAnother = new Monster(0, 4, 1.3 * wRatio, 1.3 * hRatio, 0.15, 0.4, 1000, 1000, ":/monster/quant.png");
                vecMonster.push_back(monAnother);
            }
        }
    }
    // 更新地图
    update();
}

void myMainWindow::paintTower(QPainter * painter)
{
    Tower * towerSearcher = NULL;
    // 从向量中读取塔信息
    for (int i = vecTower.size() - 1; i >= 0; i--) {
        towerSearcher = vecTower[i];
        QPixmap picTower(towerSearcher->strTower);
        double xTowPost = towerSearcher->arrayLocation[0];
        double yTowPost = towerSearcher->arrayLocation[1];
        double towWidth = towerSearcher->doubleWidth;
        double towHeight = towerSearcher->doubleHeight;
        double towWidthRef = towerSearcher->doubleWidthRef;
        double towHeightRef = towerSearcher->doubleHeightRef;

        QPixmap picBullet(towerSearcher->strBullet);
        double bulWidth = towerSearcher->doubleBulWidth;
        double bulHeight = towerSearcher->doubleBulHeight;
        double bulWidthRef = towerSearcher->doubleBulWidthRef;
        double bulHeightRef = towerSearcher->doubleBulHeightRef;
        double & bullet = towerSearcher->doubleBullet;
        int chosen = towerSearcher->intMonsterChosen;

        // 塔贴图
        painter->drawPixmap((xTowPost - towWidthRef) * wRatio, (yTowPost - towHeightRef) * hRatio, towWidth, towHeight, picTower);
        // 子弹贴图
        if (chosen != -1)
        {
            double xBulPost = bullet * xTowPost + (1 - bullet) * vecMonster[chosen]->xMonPost;
            double yBulPost = bullet * yTowPost + (1 - bullet) * vecMonster[chosen]->yMonPost;
            if (bullet > 0.2)
                bullet -= 0.08;
            else
                bullet += 1;
            painter->drawPixmap((xBulPost - bulWidthRef) * wRatio, (yBulPost - bulHeightRef) * hRatio, bulWidth, bulHeight, picBullet);
        }
    }
}

void myMainWindow::paintMonster(QPainter * painter)
{
    Monster * monSearcher = NULL;
    // 从向量中读取怪物信息
    for (int i = vecMonster.size() - 1; i >= 0; i--) {
        monSearcher = vecMonster[i];
        QPixmap picMonster(monSearcher->strMonster);
        double xMonPost = monSearcher->xMonPost;
        double yMonPost = monSearcher->yMonPost;
        double monWidth = monSearcher->doubleWidth;
        double monHeight = monSearcher->doubleHeight;
        double monWidthRef = monSearcher->doubleWidthRef;
        double monHeightRef = monSearcher->doubleHeightRef;
        double xHealthRef = 0, yHealthRef = 0.5;
        double ratioHealth = (double)monSearcher->intHitPoint / monSearcher->intFullPoint;
        // 怪物贴图
        painter->drawPixmap((xMonPost - monWidthRef) * wRatio, (yMonPost - monHeightRef) * hRatio, monWidth, monHeight, picMonster);
        // 怪物生命值贴图
        if (ratioHealth > 0) {
            painter->setBrush(Qt::red);
            painter->drawRect(QRect(QPoint((xMonPost - xHealthRef) * wRatio, (yMonPost - yHealthRef) * hRatio), QPoint((xMonPost - xHealthRef + ratioHealth) * wRatio, (yMonPost - yHealthRef + 0.1) * hRatio)));

        }
    }
}

void myMainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map(":/map/map.png");
    painter.drawPixmap(0, 0, mapWidth * wRatio, mapHeight * hRatio, map);
    paintTower(&painter);
    paintMonster(&painter);
}
