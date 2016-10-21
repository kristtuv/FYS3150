TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vec3.cpp \
    euler.cpp \
    verlet.cpp \
    celestialbody.cpp \
    solarsystem.cpp \
    fullsolarsystem.cpp

HEADERS += \
    vec3.h \
    euler.h \
    verlet.h \
    celestialbody.h \
    solarsystem.h \
    fullsolarsystem.h
