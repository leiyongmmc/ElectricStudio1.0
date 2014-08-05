#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T22:24:23
#
#-------------------------------------------------

QT       += core gui svg xml

TARGET = SVG.Entity
TEMPLATE = lib
DESTDIR = ../../Bin
DEFINES += ENTITY_LIBRARY

SOURCES += \
    svgnode.cpp \
    svgnodecontainer.cpp \
    svgnodeelement.cpp \
    svgNodeElementImpl/svgrectelement.cpp \
    svgNodeElementImpl/svgellipseelement.cpp \
    svgNodeElementImpl/svglineelement.cpp \
    svgNodeElementImpl/svgpolylineelement.cpp \
    svgNodeElementImpl/svgpolygonelement.cpp \
    svgNodeElementImpl/svgcircleelement.cpp \
    svgnodeelementfactory.cpp \
    kunititem.cpp \
    kresizefocus.cpp \
    graphprimitiveprop.cpp \
    svgNodeElementImpl/svgpathelement.cpp \
    svgnodecontainerfake.cpp \
    krotateitem.cpp \
    svgNodeElementImpl/svgcirclecommonelement.cpp \
    svgNodeElementImpl/svgcirclefloorelement.cpp \
    svgpointitem.cpp \
    pointitemcontainer.cpp \
    pointitemcontainerdelegate.cpp \
    devicetype.cpp \
    svgconnectionpointcontainer.cpp \
    ilink.cpp \
    connection.cpp \
    svgNodeElementImpl/svgtextelement.cpp \
    shapeformattingsetting.cpp \
    textformattingsetting.cpp \
    itemcommand.cpp


HEADERS +=\
    entity_global.h \
    svgnode.h \
    node.h \
    svgnodecontainer.h \
    svgnodeelement.h \
    svgNodeElementImpl/svgrectelement.h \
    svgNodeElementImpl/svgellipseelement.h \
    svgNodeElementImpl/svglineelement.h \
    svgNodeElementImpl/svgpolylineelement.h \
    svgNodeElementImpl/svgpolygonelement.h \
    svgNodeElementImpl/svgcircleelement.h \
    svgnodeelementfactory.h \
    kunititem.h \
    kresizefocus.h \
    graphprimitiveprop.h \
    svgNodeElementImpl/svgpathelement.h \
    svgnodecontainerfake.h \
    krotateitem.h \
    svgNodeElementImpl/svgcirclecommonelement.h \
    svgNodeElementImpl/svgcirclefloorelement.h \
    svgpointitem.h \
    pointitemcontainer.h \
    pointitemcontainerdelegate.h \
    devicetype.h \
    svgconnectionpointcontainer.h \
    ilink.h \
    connection.h \
    svgNodeElementImpl/svgtextelement.h \
    shapeformattingsetting.h \
    textformattingsetting.h \
    itemcommand.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util
else:unix: LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util

INCLUDEPATH += $$PWD/../Util
DEPENDPATH += $$PWD/../Util
