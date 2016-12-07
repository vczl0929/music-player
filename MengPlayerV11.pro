#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T16:20:03
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MengPlayerV11
TEMPLATE = app

#INCLUDEPATH += $$PWD/include
include(Meng/Meng.pri)
include(PlayListWidget/PlayListWidget.pri)
include(Setting/Setting.pri)
include(StartMengPlayer/StartMengPlayer.pri)
include(FileDatas/FileDatas.pri)

SOURCES += main.cpp\
        musicwidget.cpp \
    musicplayer.cpp \
    runtimeinfo.cpp

HEADERS  += musicwidget.h \
    musicplayer.h \
    runtimeinfo.h

FORMS    += musicwidget.ui

DISTFILES +=

RESOURCES += \
    skins.qrc
