#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include<stdlib.h>
using namespace cv;
using namespace std;
int main()
{
	Mat Img,grayImg,gradx,blurgradx,gradAbsx,threshImg,close_threshImg,erode_threshImg,dilate_threshImg;
	Img=imread("E:\\txm1.jpg");
	imshow("0ԭͼ",Img);            
	cvtColor(Img,grayImg,COLOR_BGR2GRAY);
	imshow("1�Ҷ�ͼ",grayImg);
	Scharr(grayImg,gradx,CV_16S,1,0);
	imshow("2��Ե���ͼ",gradx);
	convertScaleAbs(gradx,gradAbsx);
	imshow("3Absͼ",gradAbsx);
    blur(gradAbsx,blurgradx,Size(5,5));
	imshow("4�˲�ͼ",blurgradx);
	threshold(blurgradx,threshImg,150,255,CV_8UC1);
	imshow("4.5��ֵ�ָ�ͼ",threshImg);
	Mat kernal=getStructuringElement(MORPH_RECT,Size(25,5));
	morphologyEx(threshImg,close_threshImg,MORPH_CLOSE,kernal);
	imshow("5�ղ���",close_threshImg);
	Mat edkl=getStructuringElement(MORPH_RECT,Size(3,3));
	erode(close_threshImg,erode_threshImg,edkl,Point(-1,-1),8);
	imshow("6��ʴ����",erode_threshImg);
	dilate(erode_threshImg,dilate_threshImg,edkl,Point(-1,-1),15);
	imshow("7���Ͳ���",dilate_threshImg);
	waitKey(0);
	return 0;

}