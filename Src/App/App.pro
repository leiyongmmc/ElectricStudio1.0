#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T22:20:41
#
#-------------------------------------------------

QT       += core gui svg sensors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SVG.App
TEMPLATE = app

DESTDIR = ../../Bin

MOC_DIR = ../../Builder/App
OBJECTS_DIR = ../../Builder/App
UI_HEADERS_DIR = ../../Builder/App

TRANSLATIONS = app_trans_ch.ts

SOURCES += main.cpp\
        mainwindow.cpp \
        graphicsscene.cpp \
        graphicsview.cpp \
        toolboxtoolbar.cpp \
        toolboxwidget.cpp \
    resourcelibrary.cpp \
    resourcemanager.cpp \
    svgitem.cpp \
    griddialog.cpp \
    gridsetting.cpp \
    test.cpp \
    appmanager.cpp \
    appcommand.cpp \
    Trigger/actionmanager.cpp \
    Trigger/menumanager.cpp \
    Trigger/toolbarmanager.cpp \
    Trigger/toolbar.cpp \
    Trigger/maintoolbar.cpp \
    Trigger/editortoolbar.cpp \
    Trigger/arrangetoolbar.cpp \
    Trigger/shapeformattingtoolbar.cpp \
    Trigger/textformattingtoolbar.cpp \
    Trigger/locationandsizetoolbar.cpp \
    Trigger/triggermanager.cpp \
    optionsdialog.cpp \
    appglobal.cpp \
    FileInfo/fileservice.cpp \
    Grid/coordinateframe.cpp \
    resourcetreewidget.cpp \
    Property/electricpropertytablewidget.cpp \
    Property/propertiesandstyletoolbar.cpp \
    Property/propertiesandstylewidget.cpp \
    alignitems.cpp \			
    Trigger/statubar.cpp


HEADERS  += mainwindow.h \
        graphicsscene.h \
        graphicsview.h \
        toolboxtoolbar.h \
        toolboxwidget.h \
    resourcelibrary.h \
    resourcemanager.h \
    svgitem.h \
    griddialog.h \
    gridsetting.h \
    appmanager.h \
    appcommand.h \
    Trigger/actionmanager.h \
    Trigger/menumanager.h \
    Trigger/toolbarmanager.h \
    Trigger/toolbar.h \
    Trigger/maintoolbar.h \
    Trigger/editortoolbar.h \
    Trigger/arrangetoolbar.h \
    Trigger/shapeformattingtoolbar.h \
    Trigger/textformattingtoolbar.h \
    Trigger/locationandsizetoolbar.h \
    Trigger/triggermanager.h \
    optionsdialog.h \
    appglobal.h \
    FileInfo/fileservice.h \
    Grid/coordinateframe.h \
    resourcetreewidget.h \
    Property/electricpropertytablewidget.h \
    Property/propertiesandstyletoolbar.h \
    Property/propertiesandstylewidget.h \
    alignitems.h \
    Trigger/statubar.h

FORMS    += \
    griddialog.ui \
    optionsdialog.ui \
    Grid/coordinateframe.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util
else:unix: LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Util

INCLUDEPATH += $$PWD/../Util
DEPENDPATH  += $$PWD/../Util


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity
else:unix: LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.Entity

INCLUDEPATH += $$PWD/../Entity
DEPENDPATH += $$PWD/../Entity

RESOURCES += \
    ../Images/Images.qrc \
    ../Theme/Theme.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.IO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.IO
else:unix: LIBS += -L$$OUT_PWD/../../Bin/ -lSVG.IO

INCLUDEPATH += $$PWD/../IO
DEPENDPATH += $$PWD/../IO
