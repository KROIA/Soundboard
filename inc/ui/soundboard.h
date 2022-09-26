#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <QMainWindow>
#include "soundboardRibbon.h"

// Bastel
#include <QMediaPlayer>
#include <QAudioOutput>

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

    private:
        Ui::Soundboard *ui;
        SoundboardRibbon *m_ribbon;

        // Bastel
        QMediaPlayer *player;
        QAudioOutput *audioOutput;
};
#endif // SOUNDBOARD_H
