#pragma once


#include "registrySettings.h"

class UserSettings : public RegistrySettings
{
    public:
        UserSettings();
        ~UserSettings();

        void save() override;
        void read() override;

        const std::string &getAudioRootPath() const;
        void setAudioRootPath(const std::string &path);

        size_t getDefaultStackSize() const;
        void setDefaultStackSize(size_t size);

        int getButtonFontSize() const;
        void setButtonFontSize(int size);

        unsigned int getButtonSize() const;
        void setButtonSize(unsigned int size);

    private slots:
        void onAudoRootPathChanged(const std::string &value);
        void onDefaultStackSizeChanged(const std::string &value);
        void onButtonFontSizeChanged(const std::string &value);
        void onButtonSizeChanged(const std::string &value);
    private:
        RegistryParameter m_audioRootPath;
        RegistryParameter m_defaultStackSize;
        RegistryParameter m_buttonFontSize;
        RegistryParameter m_buttonSize;
};
