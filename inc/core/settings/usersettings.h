#pragma once


#include "registrySettings.h"

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The UserSettings class
 * \details The UserSettings class is used to save all user specific settings
 *
 */
class UserSettings : public RegistrySettings
{
    public:
        UserSettings();
        ~UserSettings();

        /**
         * \brief Saves all usersettings
         */
        void save() override;

        /**
         * \brief Reads all usersettings
         */
        void read() override;

        /**
         * \return the audio root path which is used in the QFileDialog
         */
        const std::string &getAudioRootPath() const;

        /**
         * \brief Sets the audio root path for the QFileDialog
         * \param path to a folder
         */
        void setAudioRootPath(const std::string &path);

        /**
         * \brief Gets the default sound stack size.
         * \details The size of how many sounds can be played overlapping each other
         *          for the same sound button
         * \return the stacksize
         */
        size_t getDefaultStackSize() const;

        /**
         * \brief Sets the default sound stack size
         * \param size of how many sounds can be played overlapping each other
         *        for the same sound button
         */
        void setDefaultStackSize(size_t size);

        /**
         * \return the SoundButton font size
         */
        int getButtonFontSize() const;

        /**
         * \brief Sets the SoundButton font size
         * \param size of the SoundButton text
         */
        void setButtonFontSize(int size);

        /**
         * \return the SoundButton size in pixels
         */
        unsigned int getButtonSize() const;

        /**
         * \brief Sets the SoundButton size in pixels
         * \param size of the button x and y
         */
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
