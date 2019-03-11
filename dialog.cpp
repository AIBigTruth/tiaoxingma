//上位机界面
#include "dialog.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    videoWindow=new QLabel();                     //视频窗口接口
    videoWindow->setMinimumSize(640,480);         //设置窗口大小
    startBtn=new QPushButton("start");            //设置开始按钮图形标识为start
    showBtn=new QPushButton("show");              //设置显示按钮图形标识为show
    showBtn->setVisible(false);                   //设置为不可见
    continueBtn=new QPushButton("continue");      //设置继续按钮图形标识为continue
    continueBtn->setDisabled(true);               //设置为不可用
    lineEdit=new QLineEdit();
    rightLayout=new QVBoxLayout();
    mainLayout=new QHBoxLayout(this);

    rightLayout->addWidget(startBtn);
    rightLayout->addWidget(showBtn);
    rightLayout->addWidget(continueBtn);
    rightLayout->addStretch();
    rightLayout->addWidget(lineEdit);
    mainLayout->addWidget(videoWindow);
    mainLayout->addLayout(rightLayout);             //布局

    stream=new VideoStream();
    timer=new QTimer();


    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(StartCap()));
    connect(showBtn,SIGNAL(clicked(bool)),this,SLOT(test()));
    connect(continueBtn,SIGNAL(clicked(bool)),this,SLOT(continueEve()));
    connect(timer,SIGNAL(timeout()),this,SLOT(showVideo()));
    connect(stream,SIGNAL(getStr(QString)),this,SLOT(showRes(QString)));
    connect(this,SIGNAL(startCacu()),stream,SLOT(setStart()));       //信号与槽的链接

}

Dialog::~Dialog()          //析构函数，释放空间
{
    qDebug()<<"1231";
    timer->stop();
    stream->terminate();
    delete stream;
}

void Dialog::showVideo()
{
    Mat mat;
    stream->GetStream().copyTo(mat);        //获取图像
    cvtColor(mat,mat,CV_BGR2RGB);           //灰度化
    Img=new QImage(mat.data,mat.cols,mat.rows,QImage::Format_RGB888);  //获取图像信息
    videoWindow->setPixmap(QPixmap::fromImage(*Img));         //setPixmap屏幕显示最佳化设计
    delete Img;

}

void Dialog::test()                          //测试函数
{
    Mat mat;
    stream->test().copyTo(mat);
    imshow("12111",mat);
}

void Dialog::showRes(QString res)            //复位函数
{
    lineEdit->setText(res);
    timer->stop();
    continueBtn->setEnabled(true);           //扫出条形码后停止，continue按钮变可用
}

void Dialog::continueEve()                   //按钮函数
{

    continueBtn->setDisabled(true);          //设置为不可用
    emit startCacu();                        //发送开始的信号
    timer->start(30);
}


void Dialog::StartCap()                       //开始函数
{
    stream->OpenCap();
    stream->start();
    timer->start(30);
    startBtn->setDisabled(true);
}
