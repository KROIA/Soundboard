#include "usersettings.h"
#include "ui_soundSettings.h"
#include "LaunchpadButton.h"
#include "sound.h"
#include <QCoreApplication>

UserSettings::UserSettings()
    :   RegistrySettings("HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\SoundBoard",
                         "Benutzer Einstellungen")
{
    m_audioRootPath.setMaxCharCount(200);
    m_defaultStackSize.setIntRange(2,50);
    m_buttonFontSize.setIntRange(0,50);
    m_buttonSize.setIntRange(5,1000);

    addParameter(&m_audioRootPath,
                 "audioRootPath",
                 "Audio Quellen Ordner",
                 "Pfad zum Ordner, wo der Filebrowser geöffnet wird um Sounds zu suchen.",
                  QCoreApplication::applicationDirPath().toStdString()+"/sounds");

    addParameter(&m_defaultStackSize,
                 "defaultStackSize",
                 "Standard Anzahl stackbarer Sounds",
                 "Wieviele Sounds pro Launchpadbutton gleichzeitig abgespielt werden können.",
                  (int)Sound::getDefaultStackSize());

    addParameter(&m_buttonFontSize,
                 "buttonFontSize",
                 "Textgrösse der Launchpadbuttons",
                 "Textgrösse der auf dem Launchpadbutton angezeigten Textes",
                  LaunchpadButton::getFontSize());

    addParameter(&m_buttonSize,
                 "buttonSize",
                 "Launchpadbutton size",
                 "Grösse in Pixel der Launchpadbuttons",
                  (int)LaunchpadButton::getWidth());


    connect(&m_audioRootPath, &RegistryParameter::valueChanged, this, &UserSettings::onAudoRootPathChanged);
    connect(&m_defaultStackSize, &RegistryParameter::valueChanged, this, &UserSettings::onDefaultStackSizeChanged);
    connect(&m_buttonFontSize, &RegistryParameter::valueChanged, this, &UserSettings::onButtonFontSizeChanged);
    connect(&m_buttonSize, &RegistryParameter::valueChanged, this, &UserSettings::onButtonSizeChanged);


}
UserSettings::~UserSettings()
{
    clear();
}

void UserSettings::save()
{
    RegistrySettings::save();
}
void UserSettings::read()
{
    RegistrySettings::read();
    UI_SoundSettings::setDefaultFilebrowserPath(getAudioRootPath());
    Sound::setDefaultStackSize(getDefaultStackSize());
    LaunchpadButton::setFontSize(getButtonFontSize());
    LaunchpadButton::setSize(getButtonSize(), getButtonSize());
}

const std::string &UserSettings::getAudioRootPath() const
{
    return m_audioRootPath.getValueStr();
}
void UserSettings::setAudioRootPath(const std::string &path)
{
    m_audioRootPath.setValueStr(path);
    UI_SoundSettings::setDefaultFilebrowserPath(path);
}
size_t UserSettings::getDefaultStackSize() const
{
    return m_defaultStackSize.getValueInt();
}

void UserSettings::setDefaultStackSize(size_t size)
{
    m_defaultStackSize.setValueInt(size);
    Sound::setDefaultStackSize(size);
}


int UserSettings::getButtonFontSize() const
{
    return m_buttonFontSize.getValueInt();
}

void UserSettings::setButtonFontSize(int size)
{
    m_buttonFontSize.setValueInt(size);
    LaunchpadButton::setFontSize(size);
}


unsigned int UserSettings::getButtonSize() const
{
    return m_buttonSize.getValueInt();
}

void UserSettings::setButtonSize(unsigned int size)
{
    m_buttonSize.setValueInt(size);
    LaunchpadButton::setSize(size, size);
}
void UserSettings::onAudoRootPathChanged(const std::string &value)
{
    UI_SoundSettings::setDefaultFilebrowserPath(getAudioRootPath());
}

void UserSettings::onDefaultStackSizeChanged(const std::string &value)
{
    Sound::setDefaultStackSize(getDefaultStackSize());
}

void UserSettings::onButtonFontSizeChanged(const std::string &value)
{
    LaunchpadButton::setFontSize(getButtonFontSize());
}

void UserSettings::onButtonSizeChanged(const std::string &value)
{
    LaunchpadButton::setSize(getButtonSize(), getButtonSize());
}
