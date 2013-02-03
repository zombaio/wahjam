######################################################################
# Automatically generated by qmake (2.01a) Sun Apr 8 19:07:53 2012
######################################################################

# Version number in <major>.<minor>.<patch> form
VERSION = 0.6.0
DEFINES += VERSION=\'\"$$VERSION\"\'
DEFINES += COMMIT_ID=\'\"$$system(git rev-parse HEAD)\"\'

TEMPLATE = app
TARGET = wahjamsrv
DEPENDPATH += .
INCLUDEPATH += ..
QT -= gui
QT += network

# Code in common/ does not use wide characters
win32:DEFINES -= UNICODE

# Build console application
win32:CONFIG += console

unix {
    HEADERS += SignalHandler.h
    SOURCES += SignalHandler.cpp
}

# Input
HEADERS += usercon.h \
           Server.h \
           logging.h \
           ninjamsrv.h \
           ../common/netmsg.h \
           ../WDL/queue.h \
           ../WDL/heapbuf.h \
           ../common/mpb.h \
           ../WDL/string.h \
           ../WDL/sha.h \
           ../WDL/ptrlist.h \
           ../WDL/rng.h \
           ../WDL/lineparse.h
SOURCES += ninjamsrv.cpp \
           logging.cpp \
           usercon.cpp \
           Server.cpp \
           ../common/netmsg.cpp \
           ../common/mpb.cpp \
           ../WDL/sha.cpp \
           ../WDL/rng.cpp
