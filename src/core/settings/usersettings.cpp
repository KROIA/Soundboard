#include "usersettings.h"
#include "ui_soundSettings.h"

UserSettings::UserSettings()
    :   RegistrySettings("HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\SoundBoard",
                         "Benutzer Einstellungen")
{
    addParameter(&m_audioRootPath,
                 "audioRootPath",
                 "Audio Quellen Ordner",
                 "Pfad zum Ordner, wo der Filebrowser geöffnet wird um Sounds zu suchen.",
                 "C:\\");
}

void UserSettings::save()
{
    RegistrySettings::save();
}
void UserSettings::read()
{
    RegistrySettings::read();
    UI_SoundSettings::setDefaultFilebrowserPath(getAudioRootPath());
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
