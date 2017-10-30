TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    toHexadecimal.cpp \
    helperFunctions.cpp

HEADERS += \
    repeated-byte-compression.hpp

