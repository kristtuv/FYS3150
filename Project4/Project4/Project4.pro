TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



SOURCES += main.cpp \
    lib.cpp

HEADERS += \
    lib.h
INCLUDEPATH += \
    /usr/local/include
    /usr/local/lib


LIBS += \
    #-LC:\Armadillo\lib32 \
    -llapack \
    -lblas
