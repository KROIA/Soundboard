#pragma once


#include "registrySettings.h"

class UserSettings : public RegistrySettings
{
    public:
        UserSettings();

        void save() override;
        void read() override;

        const std::string &getAudioRootPath() const;
        void setAudioRootPath(const std::string &path);

    private:
        RegistryParameter m_audioRootPath;
};
