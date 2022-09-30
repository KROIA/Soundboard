#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <QMainWindow>
#include "soundboardRibbon.h"

#include "debug.h"

#include "ui_sound.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Soundboard; }
QT_END_NAMESPACE

class Soundboard : public QMainWindow
{
        Q_OBJECT

    public:
        Soundboard(QWidget *parent = nullptr);
        ~Soundboard();

    private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

    private:
        Ui::Soundboard *ui;
        SoundboardRibbon *m_ribbon;

        UI_Sound *m_sound;
};
#endif // SOUNDBOARD_H
