#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T21:11:13
#
#-------------------------------------------------

QT       = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SVG.Util
TEMPLATE = lib
DESTDIR = ../../Bin
DEFINES += UTIL_LIBRARY

SOURCES += util.cpp \
    colortransformer.cpp \
    svghelper.cpp

HEADERS += util.h\
        util_global.h \
    colortransformer.h \
    svghelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}



