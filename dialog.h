#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <videoio.h>
#include <videostream.h>
#include <QTimer>
#include <QEvent>
#include <opencv2/opencv.hpp>
#include <QLineEdit>
#include <QThread>                // QThread类提供了一个与平台无关的管理线程的方法
using namespace cv;



class Dialog : public QDialog
{
    Q_OBJECT          //只有加入这个宏才能使用信号和槽的机制

public:
    Dialog(QWidget *parent = 0);//其中参数 parent 指向父窗口，参数为 0，则窗口成为一个顶级窗口
    ~Dialog();   //析构函数，释放空间

private:
    QLabel *videoWindow;//视频、图像的显示
    QImage *Img;    //QImage类封装了对于一般图像像素级的操作，原图像
    QPushButton *startBtn;//开始命令按钮
    QPushButton *showBtn;
    QPushButton *continueBtn;//继续命令按钮
    QHBoxLayout *mainLayout;//水平布局，在水平方向上排列控件，即：左右排列
    QVBoxLayout *rightLayout;//垂直布局，在垂直方向上排列控件，即：上下排列
    VideoStream *stream;    //视频流
    QTimer *timer;          //定时器，提供了定时器信号和单触发定时器
    QLineEdit *lineEdit;  //单行文本输入

signals:                 //信号  
    void startCacu();     
public slots:            //槽
    void StartCap();             //开始函数
    void showVideo();            //显示函数
    void test();                 //测试函数
    void showRes(QString res);   //复位函数
    void continueEve();          //按钮函数
protected:
};

#endif // DIALOG_H
