#-------------------------------------------------
#
# Project created by QtCreator 2013-01-13T17:37:21
#
#-------------------------------------------------

QT       -= gui

TARGET = QMDMF
TEMPLATE = lib

DEFINES += QMDMF_LIBRARY

SOURCES += qmdmf.cpp

HEADERS += qmdmf.h\
        QMDMF_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:DEFINES += _TTY_POSIX_

