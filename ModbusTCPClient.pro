QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = $$PWD/../exe
TARGET = app

SOURCES += \
    main.cpp \
    modbustcpclient.cpp \
    src/modbus-data.c \
    src/modbus-tcp.c \
    src/modbus.c

HEADERS += \
    modbustcpclient.h

FORMS += \
    modbustcpclient.ui


INCLUDEPATH += $$PWD/inc
LIBS += -L$$PWD/lib -lWS2_32

