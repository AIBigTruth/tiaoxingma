#ifndef ANALYZER_H
#define ANALYZER_H
#include <opencv2/opencv.hpp>    //包含所有的Opencv头文件
#include <QObject>

#include <QString>
using namespace cv;

class classis{
public:
    classis(int pos,int wid){
        this->pos=pos;
        this->wid=wid;
    }
public:
    int pos;
    int wid;
};
class Analyzer:public QObject
{
    Q_OBJECT
public:
    Analyzer();
    bool ImgtoNum(int pnum);
    void getSize(int startPos,int width,Mat Img_2zhi,std::vector<classis> *blackBar,std::vector<classis> *whiteBar);
    void cacuDig(std::vector<classis> blackBar, std::vector<classis> whiteBar, int result[], int preNum);
    bool checkOut(int result[], int prenum);
private:
    Mat rawImg;
    bool startFlag;

public slots:
    void receiveImg(Mat rawImg);
    void setStart();
signals:
    void successGet(QString);
};

#endif // ANALYZER_H
