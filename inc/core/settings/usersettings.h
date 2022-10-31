#pragma once


#include "registrySettings.h"

class UserSettings : public RegistrySettings
{
    public:
        UserSettings()
            :   RegistrySettings("HKEY_CURRENT_USER\\Software\\Qt\\Qt Apps\\SoundBoard",
                                 "Benutzer Einstellungen")
        {
            addParameter(&m_audioRootPath,
                         "audioRootPath",
                         "Audio Quellen Ordner",
                         "Pfad zum Ordner, welcher alle Audiodateien beinhaltet.",
                         "C:\\");
        }

        const std::string &getAudioRootPath() const { return m_audioRootPath.getValueStr(); }
        void setAudioRootPath(const std::string &path) { m_audioRootPath.setValueStr(path); }

    private:
        RegistryParameter m_audioRootPath;
};
