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
    bool addSound(Sound *sound, bool overwrite = true);
    bool addSound(const std::vector<Sound *> &sounds, bool overwrite = true);


private slots:
    void on_bottomAddButton_clicked();

    void on_topAddButton_clicked();

private:
    LaunchpadButton *createNewButton(Coord pos);

    Ui::UI_Launchpad *ui;
   // QPushButton *chliiZumUsprobiere;
    std::vector<std::vector<QPushButton*>> buttonArray;
    size_t m_gridSizeX;
    size_t m_gridSizeY;
    unsigned int buttonSize;
};

#endif // UI_LAUNCHPAD_H
