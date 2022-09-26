QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(Extern/QT-Ribbon-Widget/QT-Ribbon-Widget.pri)

inc = inc/
src = src/

INCLUDEPATH += $$inc \
               $$inc/ui \
               $$inc/core

SOURCES += \
    $$src/core/main.cpp \
    $$src/ui/soundboard.cpp \
    src/ui/soundboardRibbon.cpp

HEADERS += \
    $$inc/ui/soundboard.h \
    inc/ui/soundboardRibbon.h

FORMS += \
    ui/soundboard.ui

RC_FILE = icon.qrc

RESOURCES += \
    resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target