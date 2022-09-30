#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QDialog>
#include "ui_settingspage.h"



namespace Ui {
class UI_Settings;
}

class UI_Settings : public QDialog
{
        Q_OBJECT

    public:
        explicit UI_Settings(QWidget *parent = nullptr);
        ~UI_Settings();

        void addSettings(RegistrySettings *settings);
        void removeSettings(RegistrySettings *settings);
        void clear();

        void onShow();
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

        vector<SettingsPair> m_settings;
};

#endif // UI_SETTINGS_H
