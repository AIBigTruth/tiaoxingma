#-------------------------------------------------
#
# Project created by QtCreator 2018-05-01T02:36:45
#
#-------------------------------------------------

QT       += core gui   #核心图形用户界面

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 4-4-tiaoxingma
TEMPLATE = app


INCLUDEPATH+=E:\MySoft\OpenCV\opencv\build\include     #包含路径

             E:\MySoft\OpenCV\opencv\build\include\opencv

             E:\MySoft\OpenCV\opencv\build\include\opencv2

LIBS += E:\MySoft\OpenCV\build_qt\lib\libopencv_*.a   #包含的库

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS    #当Qt的某些功能被标记为过时的,那么编译器会发出警告

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
                                                       #禁用在Qt 6.0.0之前弃用的所有API

SOURCES += main.cpp\
        dialog.cpp \
    videoio.cpp \
    videostream.cpp \
    posmatch.cpp \
    analyzer.cpp

HEADERS  += dialog.h \
    videoio.h \
    videostream.h \
    posmatch.h \
    analyzer.h
