#include "ui_settings.h"
#include "ui_ui_settings.h"


UI_Settings::UI_Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_Settings)
{
    ui->setupUi(this);
}

UI_Settings::~UI_Settings()
{
    clear();
    delete ui;
}

void UI_Settings::addSettings(RegistrySettings *settings)
{
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        if(m_settings[i].settings == settings)
            return;
    }

    UI_SettingsPage *page = new UI_SettingsPage(this,settings);

    ui->tabWidget->addTab(page,settings->getGroupName().c_str());

    m_settings.push_back(SettingsPair{settings, page});
}
void UI_Settings::removeSettings(RegistrySettings *settings)
{
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        if(m_settings[i].settings == settings)
        {
            delete m_settings[i].ui;
            m_settings.erase(m_settings.begin()+i);
            ui->tabWidget->removeTab(i);
            return;
        }
    }
}
void UI_Settings::clear()
{
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        delete m_settings[i].ui;

    }
    ui->tabWidget->clear();
    m_settings.clear();
}
void UI_Settings::onShow()
{
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        m_settings[i].ui->onShow();
    }
}
void UI_Settings::onSave()
{
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        m_settings[i].ui->onSave();
    }
}

void UI_Settings::on_buttonBox_accepted()
{
    onSave();
    for(size_t i=0; i<m_settings.size(); ++i)
    {
        m_settings[i].settings->save();
    }
    this->hide();
}
void UI_Settings::on_buttonBox_rejected()
{
    /*for(size_t i=0; i<m_settings.size(); ++i)
    {
        m_settings[i].settings->undoValueChange();
    }*/
    this->hide();
}

