#ifndef UI_SETTINGSPAGE_H
#define UI_SETTINGSPAGE_H

#include <QWidget>
#include <vector>
#include "ui_setting.h"
#include "registrySettings.h"

#define UI_SETTINGS_PAGE_DEBUG

using std::vector;

namespace Ui {
class UI_SettingsPage;
}

class UI_SettingsPage : public QWidget
{
        Q_OBJECT

    public:
        explicit UI_SettingsPage(QWidget *parent,
                                 RegistrySettings *settings);
        ~UI_SettingsPage();

        void onShow();
        void onSave();



    private:
        Ui::UI_SettingsPage *ui;
        RegistrySettings *m_settings;
        vector<UI_Setting*> m_ui_settings;
};

#endif // UI_SETTINGSPAGE_H
