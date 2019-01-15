TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    cooleytukey.cpp

HEADERS += \
    cooleytukey.h \
    fft_exec.hpp \
    fft_table.hpp \
    goodthomas.h

INCLUDEPATH += /usr/local/Cellar/boost/1.68.0_1/include
LIBS += -L//usr/local/Cellar/boost/1.68.0_1/lib
