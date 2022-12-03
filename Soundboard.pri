QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(Extern/Qt-Ribbon-Widget/RibbonWidget.pri)

inc = $$PWD/inc
src = $$PWD/src
ui  = $$PWD/ui


INCLUDEPATH += $$inc \
               $$inc/ui \
               $$inc/core \
               $$inc/core/settings \
               $$inc/core/serialization \
               $$inc/ui/settings \

HEADERS += \
    $$inc/ui/LaunchpadButton.h \
    $$inc/core/sound.h \
    $$inc/ui/soundboard.h \
    $$inc/ui/soundboardRibbon.h \
    $$inc/core/debug.h \
    $$inc/core/soundsource.h \
    $$inc/ui/ui_soundSettings.h \
    $$inc/ui/ui_launchpad.h \
    $$inc/core/settings/registryParameter.h \
    $$inc/core/settings/usersettings.h \
    $$inc/core/settings/registrySettings.h \
    $$inc/ui/settings/ui_settings.h \
    $$inc/ui/settings/ui_settingspage.h \
    $$inc/ui/settings/ui_setting.h \
    $$inc/core/serialization/ISerializable.h \
    $$inc/core/serialization/database.h \
    $$inc/core/serialization/databaseDeclaration.h \
    $$inc/core/serialization/databaseID.h \
    $$inc/core/serialization/databaseObject.h \
    $$inc/core/soundboardDatabase.h

SOURCES += \
    $$PWD/src/core/settings/usersettings.cpp \
    $$src/ui/LaunchpadButton.cpp \
    $$src/core/sound.cpp \
    $$src/ui/soundboard.cpp \
    $$src/ui/soundboardRibbon.cpp \
    $$src/core/debug.cpp \
    $$src/core/soundsource.cpp \
    $$src/ui/ui_soundSettings.cpp \
    $$src/ui/ui_launchpad.cpp \
    $$src/core/settings/registryParameter.cpp \
    $$src/core/settings/registrySettings.cpp \
    $$src/ui/settings/ui_settings.cpp \
    $$src/ui/settings/ui_settingspage.cpp \
    $$src/ui/settings/ui_setting.cpp \
    $$src/core/serialization/ISerializable.cpp \
    $$src/core/serialization/database.cpp \
    $$src/core/serialization/databaseID.cpp \
    $$src/core/serialization/databaseObject.cpp \
    $$src/core/soundboardDatabase.cpp





FORMS += \
    $$ui/soundboard.ui \
    $$ui/settings/ui_setting.ui \
    $$ui/settings/ui_settings.ui \
    $$ui/settings/ui_settingspage.ui \
    $$ui/ui_soundSettings.ui \
    $$ui/ui_launchpad.ui



RESOURCES += \
    $$PWD/resources.qrc


