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



    m_sound = new UI_Sound(this);
    m_sound->setSource(source);
    m_sound->setVolume(1);
    m_sound->setPlaybackSpeed(1);

    QFile output("testOut.xml");
    output.open(QFile::OpenModeFlag::WriteOnly);
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    m_sound->save(&stream);

    stream.writeEndDocument();
    output.close();

    ui->scrollAreaWidgetContents->layout()->addWidget(m_sound);
}

Soundboard::~Soundboard()
{
    delete ui;
}


void Soundboard::on_pushButton_clicked()
{
    m_sound->play();
}


void Soundboard::on_pushButton_2_clicked()
{
    m_sound->pause();
}

