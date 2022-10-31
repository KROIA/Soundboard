QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

include(../../Soundboard.pri)

SOURCES +=  tst_test_database.cpp \
    ../projectInfoDummy.cpp

HEADERS += \
    apple.h \
    fruit.h \
    fruitBasket.h \
    pineapple.h
