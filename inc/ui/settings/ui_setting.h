#pragma once

#include <QWidget>
#include "registryParameter.h"

#define UI_SETTING_DEBUG

namespace Ui {
class UI_Setting;
}

/**
 * \author Alex Krieg
 * \date   12.10.2022
 *
 * \brief The UI_Setting class
 * \details This class represent a single setting value
 *
 */
class UI_Setting : public QWidget
{
        Q_OBJECT

    public:
        /**
         * \brief UI_Setting constructor
         * \param parent widget
         * \param parameter for this widget
         */
        explicit UI_Setting(QWidget *parent,
                            RegistryParameter *parameter);
        ~UI_Setting();

        /**
         * \brief Gets called when the setting is diplayed
         */
        void onShow();

        /**
         * \brief Will save the edited setting
         */
        void onSave();
    private slots:

    private:
        Ui::UI_Setting *ui;
        RegistryParameter *m_parameter;
};
