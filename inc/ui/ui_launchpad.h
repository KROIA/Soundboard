#ifndef UI_LAUNCHPAD_H
#define UI_LAUNCHPAD_H

#include <QWidget>
#include "LaunchpadButton.h"
#include <vector>

namespace Ui {
class UI_Launchpad;
}

class UI_Launchpad : public QWidget
{
    Q_OBJECT

public:
    explicit UI_Launchpad(QWidget *parent = nullptr);
    ~UI_Launchpad();
    void setButtonSize(unsigned int bs);
private slots:
    void on_bottomAddButton_clicked();

    void on_topAddButton_clicked();

private:
    Ui::UI_Launchpad *ui;
   // QPushButton *chliiZumUsprobiere;
    std::vector<std::vector<QPushButton*>> buttonArray;
    unsigned int buttonSize;
};

#endif // UI_LAUNCHPAD_H
