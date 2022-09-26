#include "soundboard.h"
#include "ui_soundboard.h"

Soundboard::Soundboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soundboard)
{
    ui->setupUi(this);
    m_ribbon = new SoundboardRibbon(ui->ribbonTabWidget);

    // Bastel
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    // ...
    player->setSource(QUrl::fromLocalFile("E:/Dokumente/QT/Projects/Soundboard/sounds/lang.mp3"));
    audioOutput->setVolume(50);

}

Soundboard::~Soundboard()
{
    delete ui;
}


void Soundboard::on_pushButton_clicked()
{
    player->play();
}

