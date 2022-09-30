#pragma once

#include <QWidget>
#include "registryParameter.h"
#include "debug.h"

#define UI_SETTING_DEBUG

namespace Ui {
class UI_Setting;
}

class UI_Setting : public QWidget
{
        Q_OBJECT

    public:
        explicit UI_Setting(QWidget *parent,
                            RegistryParameter *parameter);
        ~UI_Setting();

        void onShow();

    public slots:
        void onSave();
    private slots:

    private:
        Ui::UI_Setting *ui;
        RegistryParameter *m_parameter;
};
