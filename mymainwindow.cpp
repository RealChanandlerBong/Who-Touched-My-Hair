#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "helpdialog.h"
#include "qpoint.h"
#include "tower.h"
#include "store.h"
#include "map.h"
#include <QTime>
<<<<<<< HEAD
#include <QMouseEvent>
=======
#include <QTimer>
>>>>>>> e2fb4b3b5da3512680c537455419e0736af615d6


myMainWindow::myMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myMainWindow)
{
    ui->setupUi(this);
    this->gameState = 0;
// this->originX = 0;
// this->originY = 0;
    this->roleChoose = 0;
    this->towerType = 0;
    this->mouseState = 0;
    this->precellx = 0;
    this->precelly = 0;

    this->recMap = QRect(QPoint(0, 26), QPoint(800, 600));
    this->recTower = QRect(QPoint(200, 100), QPoint(600, 200));
    this->recMonster = QRect(QPoint(200, 400), QPoint(600, 500));

    int roadLength = 45;
    int roadLocation[45][2] = {   }; //待定

	//QTimer
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(100000);//总长100秒
	connect(fTimer,SIGNAL(timeout()),this,SLOT(update()));

 

    Map myMap(30, 20, roadLocation, roadLength);

}







myMainWindow::~myMainWindow()
{
    delete ui;
}


void myMainWindow::on_actionHelp_triggered()
{
    HelpDialog myHelpDialog;
    myHelpDialog.setModal(true);
    myHelpDialog.exec();
}

void myMainWindow::on_actionExit_triggered()
{
    this->close();
	fTimer->stop();
}

void myMainWindow::on_actionStart_triggered()
{
    this->gameState = 1;
    chooseRole();
}

<<<<<<< HEAD
void myMainWindow::mousePressEvent(QMouseEvent *event)
{//改动：store.cpp后两个函数，
        //map.cpp中MapIsOccupied()占用条件，
        //mymainwindow.h增加三个变量
    //0表示刚打开窗口，游戏未初始化，
    //3表示处于游戏暂停
    //4表示处于游戏结束
    if(event->button() == Qt::LeftButton)
    {
        int x = event->globalX();
        int y = event->globalY();
        if(gameState == 1) //1表示处于选择角色界面
        {
            //可能位置坐标要改
            if( x > recTower.topLeft().x() && x < (recTower.topLeft().x() + recTower.width())
                    && y > recTower.topLeft().y() && y < (recTower.topLeft().y() + recTower.height()))
            {
                roleChoose = 0; //玩家为塔
                gameState = 2; //游戏开始
            }
            else if(x > recMonster.topLeft().x() && x < (recMonster.topLeft().x() + recMonster.width())
                    && y>recMonster.topLeft().y() && y < (recMonster.topLeft().y() + recMonster.height()))
            {
                roleChoose = 1;//玩家为怪
                gameState = 2;
            }
            gameStart();
        }
        else if(gameState == 2) //2表示处于游戏进行界面
        {
            if(roleChoose == 0) //角色为塔
            {
                int cellx = int((x - 0)/11);
                int celly = int((y - 0)/17);
                store mystore=store();
                QPoint mouse=QPoint(x,y);
                int newTowerType = store::buyTower(mouse); //点商店
                if( newTowerType != -1  //点到了商店某个塔
                    && store::isAfford(newTowerType, Gold)) //钱够
                {   Tower* buyTower = new Tower(newTowerType, x, y);
                    int Towersizex = buyTower->arraySize[0];
                    int Towersizey = buyTower->arraySize[1];
                    int placeForNewTower = 0;   //是否还有位置放置该塔
                    for (int i = 0; i < myMap::sizex; i++)
                        for (int j = 0; j < myMap::sizey; i++)
                            if( myMap::MapisOccupied(i, j, Towersizex, Towersizey))
                                placeForNewTower = 1;
                    delete buyTower;
                    if( placeForNewTower)   //还有位置放该塔
                    {
                        if( mouseState == 0 )//之前未选定待建塔类型
                        {
                            Tower* buyTower = new Tower(newTowerType, x, y);//新建一个临时的选定类型塔
                            myMap::towerExisted[myMap::intTowerNumbers]=buyTower;
                            myMap::intTowerNumbers++;
                            setMouseTracking(true); //激活整个窗体的鼠标追踪事件
                            mouseMoveEvent(QMouseEvent *event);
                        }
                        else{   //之前已经选过待建塔类型，重新设置类型
                            Tower* buyTower =myMap::towerExisted[myMap::intTowerNumbers - 1];
                            delete buyTower;
                            buyTower = new Tower(newTowerType, x, y);
                            myMap::towerExisted[myMap::intTowerNumbers - 1] = buyTower;
                        }
                    }
                }

                else if( mouseState //已选定待建塔类型
                    && myMap::MapisOccupied(cellx, celly, myMap::towerExisted[myMap::intTowerNumbers - 1]->arraySize[0], myMap::towerExisted[myMap::intTowerNumbers - 1]->arraySize[1]))//该位置可建塔
                {
                    Tower* buyTower = myMap::towerExisted[intTowerNumbers - 1];
                    buyTower->arrayLocation[0] = cellx;
                    buyTower->arrayLocation[1] = celly; //更改临时塔的坐标
                    myMap::MapStateChange(cellx,celly,buyTower->arraySize[0], buyTower->arraySize[1]);//将临时塔加入地图数组，更改地图状态
                    Gold -= buyTower->intCost;//扣除钱
                    setMouseTracking(false); //关闭鼠标追踪事件
                }
                else{   //点击其他位置（目前除商店中的塔和可建塔位置），取消建塔操作
                    Tower* buyTower =myMap::towerExisted[myMap::intTowerNumbers - 1];
                    delete buyTower;
                }
            }
        }
    }
}


void myMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    ui->centralwidget->setMouseTracking(true);
    if(gameState == 2)
    {
        int x = event->globalX();
        int y = event->globalY();
        int cellx = int((x - 0)/11);
        int celly = int((y - 0)/17);
        if(myMap::MapisOccupied(cellx, celly, towerExisted[intTowerNumbers - 1]->arraySize[0], towerExisted[intTowerNumbers - 1]->arraySize[1])) //所在格子能放塔
            && (precellx != cellx || precelly != celly) //所在格子与上一时刻不同
        {
            MapStateChange(precellx,precelly,towersizex,towersizey,0);//将上一时刻Map中格子的贴图状态去掉
            MapStateChange(cellx,celly,towersizex,towersizey,2);//增加贴图状态的格子
            precellx = cellx;
            precelly = celly;//将当前时刻鼠标格子坐标记为上一时刻坐标
            /*QPoint pos = this->pos();
            pos.setX();
            pos.setY();*///根据鼠标移动位置进行跟踪贴图
        }
    }
}
=======



void myMainWindow::update()//5秒生成一个怪+每秒检查是否游戏失败
{

  int remaintime = fTimer->remainingTime(); //获取当前时间
  if(Map::Update(0)==False){
      fTimer->stop();}
      else{

      if(remaintime%500==0){//0.5 second panduanyici
          srand(remaintime);
          if(remaintime/500%(rand()%3)==0)
             myMap.ProduceMonster（0）;}

      }

}


>>>>>>> e2fb4b3b5da3512680c537455419e0736af615d6
void myMainWindow::initial()
{

}

void myMainWindow::chooseRole()
{
    //this->recTower.show();
}

void myMainWindow::gameStart()
{
	fTimer->start();//定时器开始工作
	fTimeCounter.start(); //计时器开始工作
}

void myMainWindow::produceHint(QMouseEvent *event)//判断鼠标是否悬浮在第m行n列的格子上
{

}
