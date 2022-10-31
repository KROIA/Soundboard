#include "ui_setting.h"
#include "ui_ui_setting.h"

UI_Setting::UI_Setting(QWidget *parent,
                       RegistryParameter *parameter) :
    QWidget(parent),
    ui(new Ui::UI_Setting)
{
    ui->setupUi(this);
    m_parameter = parameter;

    if(!m_parameter)
    {
#ifdef UI_SETTING_DEBUG
        CRITICAL("parameter is nullptr");
#endif
        return;
    }
    onShow();
}

UI_Setting::~UI_Setting()
{
    delete ui;
}
void UI_Setting::onShow()
{
    ui->name_label->setText(m_parameter->getReadableName().c_str());
    ui->name_label->setToolTip(m_parameter->getDescription().c_str());
    ui->lineEdit->setToolTip(m_parameter->getDescription().c_str());
    ui->spinBox->setToolTip(m_parameter->getDescription().c_str());
    ui->doubleSpinBox->setToolTip(m_parameter->getDescription().c_str());

    switch(m_parameter->getType())
    {
        case RegistryParameter::Type::stringType:
        {
            ui->stackedWidget->setCurrentIndex(0);
            ui->lineEdit->setText(m_parameter->getValueStr().c_str());
            break;
        }
        case RegistryParameter::Type::intType:
        {
            ui->stackedWidget->setCurrentIndex(1);
            ui->spinBox->setValue(m_parameter->getValueInt());
            break;
        }
        case RegistryParameter::Type::floatType:
        {
            ui->stackedWidget->setCurrentIndex(2);
            ui->doubleSpinBox->setValue(m_parameter->getValueFloat());
            break;
        }
    }
}
void UI_Setting::onSave()
{
    if(!m_parameter)return;
    switch(m_parameter->getType())
    {
        case RegistryParameter::Type::stringType:
        {
            m_parameter->setValueStr(ui->lineEdit->text().toStdString());
            break;
        }
        case RegistryParameter::Type::intType:
        {
            m_parameter->setValueInt(ui->spinBox->value());
            break;
        }
        case RegistryParameter::Type::floatType:
        {
            m_parameter->setValueFloat(ui->doubleSpinBox->value());
            break;
        }
    }
}


