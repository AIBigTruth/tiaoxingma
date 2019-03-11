//条形码定位
#include "posmatch.h"
#include <QDebug>
#include <vector>

PosMatch::PosMatch()
{
    testMat=new Mat();
    posRect=Rect(0,0,0,0);  //初始化矩形框
}

void PosMatch::setMat(Mat *mat)
{
    srcImg=mat;
}

Rect PosMatch::getPos()
{
    return posRect;
}

void PosMatch::run()
{
    Mat kernal=getStructuringElement(MORPH_RECT,Size(25,5));//膨胀时用到的kernel，MORPH_RECT：矩形，参数自己调整，实践设置得到，淹模参数25*5
    Mat edKl=getStructuringElement(MORPH_RECT,Size(3,3));//
    std::vector<std::vector<Point>> contours;
    Rect maxRe;
    while(1){
        Mat Img;
        Mat gradX;
        Mat threshImg;
        srcImg->copyTo(Img);
        int index=0;
        double maxSize=0.0;
        contours.clear();
        cvtColor(Img,Img,CV_BGR2GRAY,CV_8UC1);//灰度化
        Scharr(Img,gradX,CV_16S,1,0);//Scharr滤波器,计算图像差分：Scharr()函数,求x方向的梯度
        convertScaleAbs(gradX,gradX);//使用线性变换转换输入数组元素成8位无符号整型，计算绝对值，并将结果转化成8位
        blur(gradX,gradX,Size(5,5));//中值滤波
        threshold(gradX,threshImg,200,255,CV_8UC1);//threshold 方法是通过遍历灰度图中点，设置阈值200，将图像信息二值化,阈值分割
        morphologyEx(threshImg,threshImg,MORPH_CLOSE,kernal);//高级的形态学运算函数,MORPH_CLOSE闭操作,闭操作，先膨胀再腐蚀，将白条膨胀到淹没黑条，得到全白方块，方便定位，腐蚀能缩小还原成原来大小
        erode(threshImg,threshImg,edKl,Point(-1,-1),8);//腐蚀
        dilate(threshImg,threshImg,edKl,Point(-1,-1),15);//开操作，先腐蚀再膨胀，将除了条形码以外的其他东西去除，去燥作用
        //轮廓
        findContours(threshImg,contours,RETR_LIST,CHAIN_APPROX_NONE);//寻找轮廓，边缘检测算法，findContours是寻找边缘的函数
        for(unsigned int i=0;i<contours.size();i++){
            if(maxSize<contourArea(contours[i])){
                maxSize=contourArea(contours[i]);
                index=i;
            }
        }
        if(contours.size()>0){
            maxRe=boundingRect(contours[index]);
            rectangle(threshImg,maxRe,Scalar(155));
            posRect=maxRe;
            (*srcImg)(posRect).copyTo(*testMat);
            emit analy(*testMat);
        }else{
            posRect=Rect(0,0,0,0);
        }
        msleep(500);
    }
}
