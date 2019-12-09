#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "helpdialog.h"
#include <QTime>
#include <QTimer>


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
