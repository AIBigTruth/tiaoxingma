//摄像头设置
#include "videoio.h"

VideoIO::VideoIO()
{

}

void VideoIO::OpenCap()
{
    cap=VideoCapture(0);//0为计算机自带的摄像头，1为外接摄像头

}

void VideoIO::CloseCap()
{
    cap.release();//关闭摄像机
}

void VideoIO::GetImg(Mat *mat)
{
    bool bSuccess = cap.read(*mat);//从视频流读取帧
    if (!bSuccess)
    {
        qDebug() << "Cannot read a frame from video stream" << "\n";//无法从视频流读取帧
    }
}
