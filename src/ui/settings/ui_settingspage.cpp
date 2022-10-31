#include "ui_settingspage.h"
#include "ui_ui_settingspage.h"
#include <QVBoxLayout>

UI_SettingsPage::UI_SettingsPage(QWidget *parent,
                                 RegistrySettings *settings) :
    QWidget(parent),
    ui(new Ui::UI_SettingsPage)
{
    ui->setupUi(this);
    m_settings = settings;
    if(!m_settings)
    {
#ifdef UI_SETTINGS_PAGE_DEBUG
        CRITICAL("settings is nullptr");
#endif
        return;
    }

    ui->gropName_label->setText(m_settings->getGroupName().c_str());

    std::vector<RegistryParameter *> params = m_settings->getParameters();
    //  QVBoxLayout *layout = new QVBoxLayout(this);
    // ui->scrollArea->setLayout(layout);

    for(size_t i=0; i<params.size(); ++i)
    {
        if(!params[i]) continue;
        UI_Setting *setting = new UI_Setting(ui->scrollAreaWidgetContents,params[i]);
        m_ui_settings.push_back(setting);

        if(ui->scrollAreaWidgetContents->layout())
        {
            ui->scrollAreaWidgetContents->layout()->addWidget(setting);

        }

    }
    if(ui->scrollAreaWidgetContents->layout())
    {
        ui->scrollAreaWidgetContents->layout()->removeItem(ui->verticalSpacer);
        ui->scrollAreaWidgetContents->layout()->addItem(ui->verticalSpacer);

    }

}

UI_SettingsPage::~UI_SettingsPage()
{
    delete ui;
}

void UI_SettingsPage::onShow()
{
    for(size_t i=0; i<m_ui_settings.size(); ++i)
    {
        m_ui_settings[i]->onShow();
    }
}
void UI_SettingsPage::onSave()
{
    for(size_t i=0; i<m_ui_settings.size(); ++i)
    {
        m_ui_settings[i]->onSave();
    }
}
