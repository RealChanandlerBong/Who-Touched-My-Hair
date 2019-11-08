#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "helpdialog.h"


myMainWindow::myMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myMainWindow)
{
    ui->setupUi(this);
    this->gameState = 0;
    this->originX = 0;
    this->originY = 0;
    this->roleChoose = 0;
    this->towerCategory = 0;
    this->dragMouse = false;
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

}

void myMainWindow::mousePressEvent(QMouseEvent *event)
{
    //0表示刚打开窗口，游戏未初始化，
    //1表示处于选择角色界面
    //2表示处于游戏进行界面
    //3表示处于游戏暂停
    //4表示处于游戏结束
    if(event->button() == Qt::LeftButton)
    {
        if(gameState == 1)
        {
            int x = event->globalX();
            int y = event->globalY();
            if()
            {
                roleChoose = 0; //玩家为塔
                gameState = 2; //游戏开始
            }
            else if()
            {
                roleChoose = 1;//玩家为怪
                gameState = 2;
            }
        }
        else if(gameState == 2)
        {
            if(         //点到了商店某个塔
                        //钱够
                    )   //还有位置放塔
            {
                towerCategory = 1; //举例
                dragMouse = true;
                originX = x;
                originY = y;
            }
            else if() //其它类似
            {

            }
        }
    }
}

void myMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(gameState == 2 && dragMouse == true)
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
