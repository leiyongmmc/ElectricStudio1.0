#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T09:38:19
#
#-------------------------------------------------

QT       -= gui

TARGET = SVG.Solver
TEMPLATE = lib
DESTDIR = ../../Bin
DEFINES += SOLVER_LIBRARY

SOURCES += \
    circuitsolver.cpp

HEADERS +=\
        solver_global.h \
    circuitsolver.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
