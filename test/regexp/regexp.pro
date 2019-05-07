QT       -= core
QT       -= gui

TARGET = regexp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.c \
    rex.c \
    reio.c \
    reec.c \


OTHER_FILES += \
    T0K.jpg \
    reec.xls \
    reec.jpg

HEADERS += \
    rex.h \
    reio.h \
    reec.h
