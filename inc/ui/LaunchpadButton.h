#pragma once

#include <QPushButton>
#include <QLabel>
#include <vector>
#include "sound.h"
#include "ui_soundSettings.h"

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The LaunchpadButton class
 * \details This class defines the pushbutton to play the sounds
 *
 */
class LaunchpadButton: public QPushButton
{
    public:
        LaunchpadButton(QWidget *parent = nullptr);
        ~LaunchpadButton();

        /**
         * \brief Binds a sound to this button
         * \param sound to bind
         */
        void setSound(Sound *sound);

        /**
         * \return the bound sound
         */
        Sound *getSound() const;

        /**
         * \brief Sets the x y pos of the button in the launchpad grid
         * \details The pos is not the pixel coordinates, it is the array coordinates
         * \param pos of the button
         */
        void setArrayPos(const Coord &pos);

        /**
         * \return the array coordinates of the button
         */
        const Coord &getArrayPos();


        /**
         * \brief Switch to the eding/play Mode of all buttons
         * \param editEnable
         */
        static void setEditMode(bool editEnable);

        /**
         * \return gets the currend mode
         *         true if editing is enabled
         *         false if playmode is active
         */
        static bool getEditMode();

        /**
         * \brief Sets the size of each button
         * \param width in pixels
         * \param height in pixels
         */
        static void setSize(unsigned int width, unsigned int height);

        /**
         * \return the width of the button in pixels
         */
        static unsigned int getWidth();

        /**
         * \return the height of the button in pixels
         */
        static unsigned int getHeight();

        /**
         * \brief Sets the fontsize of the button text
         * \param size
         */
        static void setFontSize(int size);

        /**
         * \return the fontsize of the button text
         */
        static int getFontSize();


    private slots:
        void onButtonPress();
        void onSoundDeleted();
        void onSoundNameChanged(const std::string &name);

    private:
        void createNewSound();
        void deleteThisOwnedSound();
        void setEtitMode_internal();
        void setSize_internal(unsigned int width, unsigned int height);
        void setFontSize_internal(int size);

        Sound *m_sound;
        Sound *m_thisOwnedSound;
        Coord m_buttonPos;
        QLabel *m_label;


        static bool m_editMode;
        static std::vector<LaunchpadButton*> m_buttons;
        static UI_SoundSettings *m_settingsWindow;
        static unsigned int m_width;
        static unsigned int m_height;
        static int m_fontSize;
};
