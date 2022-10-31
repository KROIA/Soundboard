#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include "soundboardRibbon.h"

#include "debug.h"
#include "usersettings.h"
#include "projectInfo.h"

#include "ui_sound.h"
#include "ui_settings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Soundboard; }
QT_END_NAMESPACE

class Soundboard : public QMainWindow
{
        Q_OBJECT

    public:
        Soundboard(QWidget *parent = nullptr);
        ~Soundboard();

    private slots:

        void on_actionVersion_triggered();
        void on_actionInfo_triggered();
        void on_actionEinstellungen_triggered();


    private:
        Ui::Soundboard *ui;
        SoundboardRibbon *m_ribbon;

        UI_Settings *m_settingsWindow;
        UserSettings m_userSettings;

        UI_Sound *m_sound;
};
