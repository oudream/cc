QT       -= core
QT       -= gui

TARGET = miniweb
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

win32: LIBS += -lwsock32 -lws2_32

SOURCES += \
#    vod.c \
    procpil.c \
    mpd.c \
    miniweb.c \
    httppost.c \
    httppil.c \
#    httpmin.c \
    httpauth.c \
    http.c

HEADERS += \
    revision.h \
    procpil.h \
    httppil.h \
    httpint.h \
    httpapi.h

