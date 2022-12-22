#pragma once

#include <QDialog>
#include "ui_settingspage.h"



namespace Ui {
class UI_Settings;
}

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The UI_Settings class
 * \details This class a widget, containing all settings pages
 *
 */
class UI_Settings : public QDialog
{
        Q_OBJECT

    public:
        /**
         * \brief UI_Settings constructor
         * \param parent widget
         */
        explicit UI_Settings(QWidget *parent = nullptr);
        ~UI_Settings();

        /**
         * \brief Adds RegistrySettings to the widget
         * \param settings to add
         */
        void addSettings(RegistrySettings *settings);

        /**
         * \brief Removes the given setting, not deleting it
         * \param settings to remove
         */
        void removeSettings(RegistrySettings *settings);

        /**
         * \brief Removes all settings, not deleting them
         */
        void clear();


        /**
         * \brief Gets called when the setting is diplayed
         */
        void onShow();

        /**
         * \brief Will save the edited setting
         */
        void onSave();


    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();

    private:
        Ui::UI_Settings *ui;

        struct SettingsPair
        {
            RegistrySettings *settings;
            UI_SettingsPage *ui;
        };

        std::vector<SettingsPair> m_settings;
};

