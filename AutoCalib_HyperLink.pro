#-------------------------------------------------
#
# Project created by QtCreator 2013-11-25T11:21:21
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AutoCalib_HyperLink
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lm -lGL -lGLU -lglut -lpthread -L/usr/lib

TEMPLATE = app

INCLUDEPATH += /usr/local/include/ /usr/local/include/tesseract /usr/local/include/leptonica
INCLUDEPATH += /usr/local/include/ /usr/local/include/opencv /usr/local/include/opencv2


LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_calib3d
LIBS += -L/usr/local/lib -llept -ltesseract -lX11


SOURCES += main.cpp \
    touchpoint.cpp \
    setup.cpp \
    pointfilter.cpp \
    detector.cpp \
    capture.cpp \
    mousecontroller.cpp \
    easytouch_ocr.cpp \
    EcTouch+Ocr+Web.cpp \
    capture_new.cpp \
    Paint.cpp

HEADERS += \
    touchpoint.h \
    setup.h \
    pointfilter.h \
    detector.h \
    capture.h \
    mousecontroller.h
