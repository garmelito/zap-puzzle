TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    engine.cpp \
    interface.cpp \
    board.cpp \
    node.cpp

HEADERS += \
    node.h \
    engine.h \
    interface.h \
    board.h \
    point.h
