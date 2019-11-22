#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "helpdialog.h"


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

    this->recMap = QRect(QPoint(0, 26), QPoint(800, 600));
    this->recTower = QRect(QPoint(200, 100), QPoint(600, 200));
    this->recMonster = QRect(QPoint(200, 400), QPoint(600, 500));

    int roadLength = 45;
    int roadLocation[45][2] = {

    }; //待定

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
}

void myMainWindow::on_actionStart_triggered()
{
    this->gameState = 1;
    chooseRole();
}

void myMainWindow::mousePressEvent(QMouseEvent *event)
{
    //0表示刚打开窗口，游戏未初始化，


    //3表示处于游戏暂停
    //4表示处于游戏结束
    if(event->button() == Qt::LeftButton)
    {
        if(gameState == 1) //1表示处于选择角色界面
        {
            int x = event->globalX();
            int y = event->globalY();
            //可能位置坐标要改
            if( x > recTower.topLeft().x() && x < (recTower.topLeft().x() + recTower.width())
                    && y>recTower.topLeft().y() && y < (recTower.topLeft().y() + recTower.height()))
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
                if(         //点到了商店某个塔
                            //钱够
                        )   //还有位置放塔
                {
                    ui->centralwidget->setMouseTracking(true);
                    setMouseTracking(true); //激活整个窗体的鼠标追踪事件

                    towerType = 1; //举例
                    if(enterLattice(event, ))
                }
                else if() //其它类似
                {

                }
        }
    }
}

void myMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(gameState == 2)
    {
        int x =event->globalX();
        int y = event->globalY();
        /*QPoint pos = this->pos();
        pos.setX();
        pos.setY();*///根据鼠标移动位置进行跟踪贴图
        if(towerCategory == 1)
        {
            //造个新塔
        }
        else if(towerCategory == 2)//类似
    }
}

void myMainWindow::initial()
{

}

void myMainWindow::chooseRole()
{
    //this->recTower.show();
}

void myMainWindow::gameStart()
{

}

void myMainWindow::produceHint(QMouseEvent *event)//判断鼠标是否悬浮在第m行n列的格子上
{

}
