TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += \
    #-LC:\Armadillo\lib32 \
    -llapack \
    -lblas
