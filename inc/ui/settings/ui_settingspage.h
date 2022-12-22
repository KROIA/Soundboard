#pragma once

#include <QWidget>
#include <vector>
#include "ui_setting.h"
#include "registrySettings.h"

#define UI_SETTINGS_PAGE_DEBUG

namespace Ui {
class UI_SettingsPage;
}

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The UI_SettingsPage class
 * \details This class represent a single setting page with multiple setting values in it
 *
 */
class UI_SettingsPage : public QWidget
{
        Q_OBJECT

    public:
        /**
         * \brief UI_SettingsPage constructor
         * \param parent widget
         * \param settings for this widget
         */
        explicit UI_SettingsPage(QWidget *parent,
                                 RegistrySettings *settings);
        ~UI_SettingsPage();


        /**
         * \brief Gets called when the setting is diplayed
         */
        void onShow();

        /**
         * \brief Will save the edited setting
         */
        void onSave();


    private:
        Ui::UI_SettingsPage *ui;
        RegistrySettings *m_settings;
        std::vector<UI_Setting *> m_ui_settings;
};
