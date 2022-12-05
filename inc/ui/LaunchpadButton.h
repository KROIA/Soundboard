#pragma once

#include <QPushButton>
#include <QLabel>
#include <vector>
#include "sound.h"
#include "ui_soundSettings.h"

class LaunchpadButton: public QPushButton
{
    public:
        LaunchpadButton(QWidget *parent = nullptr);
        ~LaunchpadButton();

        void setSound(Sound *sound);
        Sound *getSound() const;

        void setArrayPos(const Coord &pos);
        const Coord &getArrayPos();


        static void setEditMode(bool editEnable);
        static bool getEditMode();
        static void setSize(unsigned int width, unsigned int height);
        static unsigned int getWidth();
        static unsigned int getHeight();
        static void setFontSize(int size);
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
