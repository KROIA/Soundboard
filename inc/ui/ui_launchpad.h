#ifndef UI_LAUNCHPAD_H
#define UI_LAUNCHPAD_H

#include <QWidget>
#include "LaunchpadButton.h"
#include <vector>

namespace Ui {
class UI_Launchpad;
}
/**
 * \author David Feldmann
 * \date   12.10.2022
 *
 * \brief The UI_Launchpad class
 * \details This class is used to add new buttons.
 *
 */
class UI_Launchpad : public QWidget
{
    Q_OBJECT

public:
    explicit UI_Launchpad(QWidget *parent = nullptr);
    ~UI_Launchpad();
	/**
	 * addSound(...)
	 * \param sound Soundobject of the .mp3 file
	 * \param overwrite If set to true, overwrites existing button at same position
	 * \return Returns true if operation successful
	 */
    bool addSound(Sound *sound, bool overwrite = true);
	/**
	 * addSound(...)
	 * \param std::vector<sound*> Vector filled with soundobjects of .mp3 files
	 * \param overwrite If set to true, overwrites existing button at same position
	 * \return Returns true if operation successful
	 */
    bool addSound(const std::vector<Sound *> &sounds, bool overwrite = true);


private slots:
    void on_bottomAddButton_clicked();

    void on_topAddButton_clicked();

private:
    LaunchpadButton *createNewButton(Coord pos);

    Ui::UI_Launchpad *ui;
    std::vector<std::vector<QPushButton*>> buttonArray;
    size_t m_gridSizeX;
    size_t m_gridSizeY;

    //unsigned int m_buttonSize;
};

#endif // UI_LAUNCHPAD_H
