#ifndef POSMATCH_H
#define POSMATCH_H
#include <QThread>             //QThread类提供了一个与平台无关的管理线程的方法
#include <opencv2/opencv.hpp>
using namespace cv;

class PosMatch : public QThread
{
    Q_OBJECT            //只有加入这个宏才能使用信号和槽的机制
public:
    PosMatch();
    void setMat(Mat *mat);    //获得图像函数
    Rect getPos();           //矩阵对象 ，获得位置的函数
    Mat *testMat;

private:
    Mat *srcImg;         //Mat类是存储和操作OpenCV中图像的主要数据结构
    Rect posRect;        //矩阵对象

protected:
    void run();
signals:
    void analy(Mat);
};

#endif // POSMATCH_H
