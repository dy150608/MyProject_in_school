#-------------------------------------------------
#
# Project created by QtCreator 2019-09-03T20:05:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mplayer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    lyric_decom.cpp \
    gb2312_ucs2.c \
    probar.cpp

HEADERS  += widget.h \
    lyric_decom.h \
    gb2312_ucs2.h \
    probar.h

FORMS    += widget.ui \
    probar.ui

RESOURCES += \
    images.qrc
