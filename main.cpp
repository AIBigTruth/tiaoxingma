//主函数
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);        //QApplication 类管理图形用户界面应用程序的控制流和主要设置
    Dialog w;
    w.show();

    return a.exec();
}
