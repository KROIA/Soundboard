QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(Extern/QT-Ribbon-Widget/QT-Ribbon-Widget.pri)

inc = inc
src = src

INCLUDEPATH += $$inc \
               $$inc/ui \
               $$inc/core \
               $$inc/core/settings \
               $$inc/core/serialization \
               $$inc/ui/settings \

HEADERS += \
    $$inc/core/sound.h \
    $$inc/ui/soundboard.h \
    $$inc/ui/soundboardRibbon.h \
    $$inc/core/debug.h \
    $$inc/core/soundsource.h \
    $$inc/ui/ui_sound.h \
    $$inc/core/settings/registryParameter.h \
    $$inc/core/settings/usersettings.h \
    $$inc/core/settings/registrySettings.h \
    $$inc/ui/settings/ui_settings.h \
    $$inc/ui/settings/ui_settingspage.h \
    $$inc/ui/settings/ui_setting.h \
    $$inc/core/serialization/ISerializable.h \
    inc/core/serialization/database.h

SOURCES += \
    $$src/core/main.cpp \
    $$src/core/sound.cpp \
    $$src/ui/soundboard.cpp \
    $$src/ui/soundboardRibbon.cpp \
    $$src/core/debug.cpp \
    $$src/core/soundsource.cpp \
    $$src/ui/ui_sound.cpp \
    $$src/core/settings/registryParameter.cpp \
    $$src/core/settings/registrySettings.cpp \
    $$src/ui/settings/ui_settings.cpp \
    $$src/ui/settings/ui_settingspage.cpp \
    $$src/ui/settings/ui_setting.cpp \
    $$src/core/serialization/ISerializable.cpp \
    src/core/serialization/database.cpp





FORMS += \
    ui/soundboard.ui \
    ui/settings/ui_setting.ui \
    ui/settings/ui_settings.ui \
    ui/settings/ui_settingspage.ui \
    ui/ui_sound.ui

RC_FILE = icon.qrc

RESOURCES += \
    resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
