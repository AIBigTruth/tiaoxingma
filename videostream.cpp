//视频流接口
#include "videostream.h"
#include <videoio.h>
#include <QMetaType>
#include <QString>

VideoStream::VideoStream()
{
    capIo=new VideoIO();
    Img=new Mat();
    ImgS=new Mat();
    posMatch=new PosMatch();
    posMatch->setMat(Img);
    analyzer=new Analyzer();
    qRegisterMetaType<Mat>("Mat");
    connect(posMatch,SIGNAL(analy(Mat)),analyzer,SLOT(receiveImg(Mat)));
    connect(analyzer,SIGNAL(successGet(QString)),this,SLOT(getResult(QString)));
    connect(this,SIGNAL(startCacu()),analyzer,SLOT(setStart()));
}

VideoStream::~VideoStream()
{
    capIo->CloseCap();
    delete capIo;
    posMatch->terminate();
    delete posMatch;
}

void VideoStream::OpenCap()
{
    capIo->OpenCap();
}

void VideoStream::CloseCap()
{
    capIo->CloseCap();
}

Mat VideoStream::GetStream()
{
    return *ImgS;
}

Mat VideoStream::test()
{
    return *posMatch->testMat;
}

void VideoStream::getResult(QString result)
{
    qDebug()<<result;
    emit getStr(result);
}

void VideoStream::setStart()
{
    emit startCacu();
}


void VideoStream::run()
{
    capIo->GetImg(ImgS);
    capIo->GetImg(Img);
    posMatch->start();
    while(1){
        capIo->GetImg(Img);
        Img->copyTo(*ImgS);
        rectangle(*ImgS,posMatch->getPos(),Scalar(255,0,0),2);
        msleep(30);
    }
}
