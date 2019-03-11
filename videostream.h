#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H
#include <QThread>
#include <videoio.h>
#include <posmatch.h>
#include <opencv2/opencv.hpp>
#include <analyzer.h>
using namespace cv;

class VideoStream : public QThread
{
    Q_OBJECT
public:
    VideoStream();
    ~VideoStream();
    void OpenCap();
    void CloseCap();
    Mat GetStream();
    Mat test();
private:
    VideoIO *capIo;
    Mat *Img;
    Mat *ImgS;
    PosMatch *posMatch;
    Analyzer *analyzer;
private slots:
    void getResult(QString result);
    void setStart();

protected:
    void run();
signals:
    void getStr(QString);
    void startCacu();
};

#endif // VIDEOSTREAM_H
