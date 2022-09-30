#include "soundboard.h"
#include "ui_soundboard.h"
#include "debug.h"

Soundboard::Soundboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soundboard)
{
    ui->setupUi(this);
    m_ribbon = new SoundboardRibbon(ui->ribbonTabWidget);

    //SoundSource source("C:\\Users\\alexk\\Documents\\Privat\\Softwareentwicklung\\QT\\Projekte\\Soundboard\\sounds\\lang.mp3");
    SoundSource source;
    source.setRootPath("C:\\Users\\alexk\\Documents\\Privat\\Softwareentwicklung\\QT\\Projekte\\Soundboard\\sounds");
    source.setRelativePath("lang.mp3");

    sound.setSource(source);
    sound.setVolume(1);
    sound.setPlaybackSpeed(1);
}

Soundboard::~Soundboard()
{
    delete ui;
}


void Soundboard::on_pushButton_clicked()
{
    sound.play();
}


void Soundboard::on_pushButton_2_clicked()
{
    sound.pause();
}

