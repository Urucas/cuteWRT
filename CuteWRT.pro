#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T12:44:44
#
#-------------------------------------------------

QT       += core gui phonon network webkit sql script

TARGET = CuteWRT
TEMPLATE = app

#CONFIG += mobility phonofix
CONFIG += mobility

#ICON = icon.svg

MOBILITY =

symbian {
    TARGET.UID3 = 0xe8662ec8
    TARGET.CAPABILITY = NetworkServices ReadUserData WriteUserData
    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
    TARGET.EPOCHEAPSIZE = 0x5000 0x2000000
}

MOBILITY += multimedia

SOURCES += main.cpp\
        mainwindow.cpp \
    flickcharm.cpp \
    cutewrt.cpp \
    cutewrtaudioplayer.cpp \
    cutewrtdownloadmanager.cpp \
    cutewrtdatabasemanager.cpp

HEADERS  += mainwindow.h \
    flickcharm.h \
    cutewrt.h \
    cutewrtaudioplayer.h \
    cutewrtdownloadmanager.h \
    cutewrtdatabasemanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
