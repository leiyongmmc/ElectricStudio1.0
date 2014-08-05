#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T08:36:13
#
#-------------------------------------------------

QT       += core gui svg xml

TARGET = SVG.IO
TEMPLATE = lib
DESTDIR = ../../Bin
DEFINES += IO_LIBRARY

SOURCES += \
    fileservicefactory.cpp \
    filedevicetypeservice.cpp \
    filesvgservice.cpp

HEADERS +=\
        io_global.h \
    IService.h \
    isvgservice.h \
    iservicefactory.h \
    fileservicefactory.h \
    filedevicetypeservice.h \
    idevicetypeservice.h \
    filesvgservice.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity
else:unix: LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity

INCLUDEPATH += $$PWD/../Entity
DEPENDPATH += $$PWD/../Entity
