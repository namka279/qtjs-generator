
QT += core gui widgets qml core-private v8-private qml-private
TEMPLATE = app

INCLUDEPATH += ../lib/cpgf/include/ ../metagen/build/QtCore/include ../include


CONFIG += c++11 exceptions debug

# mac + clang
# QMAKE_CFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
# QMAKE_LFLAGS += -mmacosx-version-min=10.7  -stdlib=libc++
# QMAKE_CXXFLAGS += -mmacosx-version-min=10.7  -stdlib=libc++
# QMAKE_OBJECTIVE_CFLAGS += -mmacosx-version-min=10.7
# QMAKE_CXXFLAGS += -fexceptions -ftemplate-backtrace-limit=0 -g -O0


TARGET=test

# HEADERS += QtSignalConnector.h
SOURCES += main.cpp # QtSignalConnector.cpp

SOURCES += $$files(../metagen/build/QtCore/src/*.cpp) 

LIBPATH += ../lib/cpgf/lib/
LIBS += -lcpgf
