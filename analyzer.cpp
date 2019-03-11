//条形码解析
#include "analyzer.h"
#include <qDebug>
#include <vector>
static char A[]={0x0D,0x19,0x13,0x3D,0x23,0x31,0x2F,0x3B,0x37,0x0B};//条码解析表
static char B[]={0x27,0x33,0x1B,0x21,0x1D,0x39,0x05,0x11,0x09,0x17};
static char R[]={0x72,0x66,0x6C,0x42,0x5C,0x4E,0x50,0x44,0x48,0x74};

static int ORDER[10][13]={1,1,1,1,1,1,-1,2,2,2,2,2,2,
                          1,1,0,1,0,0,-1,2,2,2,2,2,2,
                          1,1,0,0,1,0,-1,2,2,2,2,2,2,
                          1,1,0,0,0,1,-1,2,2,2,2,2,2,
                          1,0,1,1,0,0,-1,2,2,2,2,2,2,
                          1,0,0,1,1,0,-1,2,2,2,2,2,2,
                          1,0,0,0,1,1,-1,2,2,2,2,2,2,
                          1,0,1,0,1,0,-1,2,2,2,2,2,2,
                          1,0,1,0,0,1,-1,2,2,2,2,2,2,
                          1,0,0,1,0,1,-1,2,2,2,2,2,2,
                         };//EAN-13条码的奇偶次序（1表示奇次序0表示偶次序）
Analyzer::Analyzer()
{
   // ImgtoNum();
    startFlag=0;
}

bool Analyzer::ImgtoNum(int pnum)
{
    Mat Img_gray;
    cvtColor(rawImg,Img_gray,COLOR_BGR2GRAY,1);

    for(int k=70;k<150;k+=20){
        Mat Img_2zhi;
        threshold(Img_gray,Img_2zhi,k,255,THRESH_BINARY);

        int high,width;
        width=Img_2zhi.cols;
        high=Img_2zhi.rows;
        int startPos;
        startPos=1;

        QString res;

        int result[12];
        std::vector<classis> blackBar;
        std::vector<classis> whiteBar;

        //对整幅图逐行检测
        while(startPos<high){
            res="";
            getSize(startPos,width,Img_2zhi,&blackBar,&whiteBar);//获取黑白条纹的位置和宽度
            cacuDig(blackBar,whiteBar,result,pnum);//解析成数字
            if(checkOut(result,pnum)){//校验
                for(int i=0;i<12;i++){
                    res+=QString::number(result[i],10);
                }
                emit successGet(QString::number(pnum)+res);
                return true;
            }

            startPos+=2;
        }
    }
    return false;
}
//
void Analyzer::getSize(int startPos, int width, Mat Img_2zhi, std::vector<classis> *blackBar, std::vector<classis> *whiteBar)
{
    blackBar->clear();
    whiteBar->clear();
    int tempBlackPos=-1;
    int tempWhitePos=-1;
    int isBlack=0;
    for(int j=0;j<width;j++){
        if(Img_2zhi.at<uchar>(startPos,j)==0){
            if(isBlack==0){
                if(tempBlackPos!=-1){
                    (*blackBar).push_back(classis(tempBlackPos,tempWhitePos-tempBlackPos));
                }
                tempBlackPos=j;
                isBlack=1;
            }
        }else{
            if(isBlack==1){
                if(tempWhitePos!=-1){
                    (*whiteBar).push_back(classis(tempWhitePos,tempBlackPos-tempWhitePos));
                }
                tempWhitePos=j;
                isBlack=0;
            }
        }

    }

    (*blackBar).push_back(classis(tempBlackPos,tempWhitePos-tempBlackPos));
}

void Analyzer::cacuDig(std::vector<classis> blackBar, std::vector<classis> whiteBar, int result[],int preNum)
{
    float num1,num2,num3,num4;
    float temp1,temp2,temp3,temp4;
    int scalar1,scalar2,scalar3,scalar4;

    bool findit=0;
    if((blackBar.size()==30)&&(whiteBar.size()==29)){
        for(int i=0;i<13;i++){
            if(i==6){
                continue;
            }
            switch(ORDER[preNum][i]){
            case 1:
            {
                num2=(float)blackBar[i*2+2].wid;
                num4=(float)blackBar[i*2+1+2].wid;
                num1=(float)whiteBar[i*2+1].wid;
                num3=(float)whiteBar[i*2+1+1].wid;

                temp1=num1*(7.0)/(num1+num2+num3+num4);
                temp2=num2*(7.0)/(num1+num2+num3+num4);
                temp3=num3*(7.0)/(num1+num2+num3+num4);
                temp4=num4*(7.0)/(num1+num2+num3+num4);

                scalar1=((int)(temp1+0.5)>(int)temp1)?(int)temp1+1:(int)temp1;
                scalar2=((int)(temp2+0.5)>(int)temp2)?(int)temp2+1:(int)temp2;
                scalar3=((int)(temp3+0.5)>(int)temp3)?(int)temp3+1:(int)temp3;
                scalar4=((int)(temp4+0.5)>(int)temp4)?(int)temp4+1:(int)temp4;

                char tempRes=0;
                if((scalar1+scalar2+scalar3+scalar4)==7){
                    for(int k=0;k<scalar2;k++){
                        tempRes=tempRes|(1<<(scalar3+scalar4+k));
                    }
                    for(int k=0;k<scalar4;k++){
                        tempRes=tempRes|(1<<k);
                    }

                }
                findit=0;
                for(int j=0;j<10;j++){
                    if(A[j]==tempRes){
                        result[i]=j;
                        findit=1;
                        break;
                    }
                }
                if(findit==0){
                    result[i]=-7;
                }
            }
                break;
            case 0:
            {

                num2=(float)blackBar[i*2+2].wid;
                num4=(float)blackBar[i*2+1+2].wid;
                num1=(float)whiteBar[i*2+1].wid;
                num3=(float)whiteBar[i*2+1+1].wid;

                temp1=num1*(7.0)/(num1+num2+num3+num4);
                temp2=num2*(7.0)/(num1+num2+num3+num4);
                temp3=num3*(7.0)/(num1+num2+num3+num4);
                temp4=num4*(7.0)/(num1+num2+num3+num4);

                scalar1=((int)(temp1+0.5)>(int)temp1)?(int)temp1+1:(int)temp1;
                scalar2=((int)(temp2+0.5)>(int)temp2)?(int)temp2+1:(int)temp2;
                scalar3=((int)(temp3+0.5)>(int)temp3)?(int)temp3+1:(int)temp3;
                scalar4=((int)(temp4+0.5)>(int)temp4)?(int)temp4+1:(int)temp4;

                char tempRes=0;
                if((scalar1+scalar2+scalar3+scalar4)==7){
                    for(int k=0;k<scalar2;k++){
                        tempRes=tempRes|(1<<(scalar3+scalar4+k));
                    }
                    for(int k=0;k<scalar4;k++){
                        tempRes=tempRes|(1<<k);
                    }

                }
                findit=0;
                for(int j=0;j<10;j++){
                    if(B[j]==tempRes){
                        result[i]=j;
                        findit=1;
                        break;
                    }
                }
                if(findit==0){
                    result[i]=-7;
                }
            }
                break;
            case 2:
            {

                num1=(float)blackBar[i*2+2].wid;
                num3=(float)blackBar[i*2+1+2].wid;
                num2=(float)whiteBar[i*2+2].wid;
                num4=(float)whiteBar[i*2+2+1].wid;

                temp1=num1*(7.0)/(num1+num2+num3+num4);
                temp2=num2*(7.0)/(num1+num2+num3+num4);
                temp3=num3*(7.0)/(num1+num2+num3+num4);
                temp4=num4*(7.0)/(num1+num2+num3+num4);

                scalar1=((int)(temp1+0.5)>(int)temp1)?(int)temp1+1:(int)temp1;
                scalar2=((int)(temp2+0.5)>(int)temp2)?(int)temp2+1:(int)temp2;
                scalar3=((int)(temp3+0.5)>(int)temp3)?(int)temp3+1:(int)temp3;
                scalar4=((int)(temp4+0.5)>(int)temp4)?(int)temp4+1:(int)temp4;

                char tempRes=0;
                if((scalar1+scalar2+scalar3+scalar4)==7){
                    for(int k=0;k<scalar1;k++){
                        tempRes=tempRes|(1<<(scalar2+scalar3+scalar4+k));
                    }
                    for(int k=0;k<scalar3;k++){
                        tempRes=tempRes|(1<<(scalar4+k));
                    }

                }
                findit=0;
                for(int j=0;j<10;j++){
                    if(R[j]==tempRes){
                        result[i-1]=j;
                        findit=1;
                        break;
                    }
                }
                if(findit==0){
                    result[i-1]=-7;
                }
            }
                break;
            default:
            {}
                break;
            }


        }
    }
}

bool Analyzer::checkOut(int result[],int prenum)
{
    int check=0;
    check=result[10]+result[8]+result[6]+result[4]+result[2]+result[0];
    check*=3;
    check+=result[9]+result[7]+result[5]+result[3]+result[1]+prenum;
    check=check%10;
    check=10-check;
    if(check==result[11]){
//        for(int i=0;i<12;i++)
//            qDebug()<<result[i]<<" ";
        for(int i=0;i<12;i++){//不这样做可能有问题
            if(result[i]<0){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

void Analyzer::receiveImg(Mat rawImg)
{
    if(!startFlag){
        rawImg.copyTo(this->rawImg);
        for(int i=9;i>=0;i--){
            if(ImgtoNum(i)){
                startFlag=1;
                break;
            }
        }
    }
}

void Analyzer::setStart()
{
    startFlag=0;
}
