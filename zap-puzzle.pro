TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    engine.cpp \
    interface.cpp

HEADERS += \
    node.h \
    engine.h \
    interface.h
