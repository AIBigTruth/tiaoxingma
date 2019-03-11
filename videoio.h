#ifndef VIDEOIO_H
#define VIDEOIO_H
#include <QDebug>
#include <opencv2/opencv.hpp>
using namespace cv;


class VideoIO                  //videoio对于视频捕获和视频编码器是一个易用的接口
{
public:
    VideoIO();
public:
    void OpenCap();            //打开摄像头函数
    void CloseCap();           //关闭摄像头函数
    void GetImg(Mat *mat);     //获取图片函数，Mat类是存储和操作OpenCV中图像的主要数据结构
private:
    VideoCapture cap;

};

#endif // VIDEOIO_H
