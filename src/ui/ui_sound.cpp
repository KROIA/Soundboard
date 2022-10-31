#include "ui_sound.h"
#include "ui_ui_sound.h"

UI_Sound::UI_Sound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_Sound)
{
    ui->setupUi(this);

    ui->play_pushButton->setIcon(QIcon(":/icons/play.png"));      ui->play_pushButton->setText("");
    ui->pause_pushButton->setIcon(QIcon(":/icons/pause.png"));    ui->pause_pushButton->setText("");
    ui->stop_pushButton->setIcon(QIcon(":/icons/stop.png"));      ui->stop_pushButton->setText("");
    ui->repeat_pushButton->setIcon(QIcon(":/icons/repeat.png"));  ui->repeat_pushButton->setText("");
    ui->settings_pushButton->setIcon(QIcon(":/icons/settings.png"));  ui->settings_pushButton->setText("");
    ui->delete_pushButton->setIcon(QIcon(":/icons/close.png"));   ui->delete_pushButton->setText("");

    connect(ui->play_pushButton,&QPushButton::clicked,this,&UI_Sound::play);
    connect(ui->pause_pushButton,&QPushButton::clicked,this,&UI_Sound::pause);
    connect(ui->stop_pushButton,&QPushButton::clicked,this,&UI_Sound::stop);
    connect(ui->repeat_pushButton,&QPushButton::toggled,this,&UI_Sound::toggleRepeat);
}

UI_Sound::~UI_Sound()
{
    delete ui;
}


void UI_Sound::setSound(const Sound &sound)
{
    m_sound = sound;
    ui->name_label->setText(m_sound.getName().c_str());
}
const Sound &UI_Sound::getSound() const
{
    return m_sound;
}

const SoundSource &UI_Sound::getSource() const
{
    return m_sound.getSource();
}
float UI_Sound::getVolume() const
{
    return m_sound.getVolume();
}
float UI_Sound::getPlaybackSpeed() const
{
    return m_sound.getPlaybackSpeed();
}
unsigned int UI_Sound::getLoops() const
{
    return m_sound.getLoops();
}
const std::string &UI_Sound::getName() const
{
    return m_sound.getName();
}/*
void UI_Sound::save(QXmlStreamWriter *writer)
{
    if(!writer) return;
    writer->writeStartElement("UI_Sound");
   // m_sound.save(writer);
    writer->writeEndElement();
}
void UI_Sound::load(QXmlStreamReader *reader)
{
    if(!reader) return;
}*/

void UI_Sound::play()
{
    m_sound.play();
}
void UI_Sound::pause()
{
    m_sound.pause();
    emit onPlaybackPaused();
}
void UI_Sound::stop()
{
    m_sound.stop();
    emit onPlaybackStopped();
}

void UI_Sound::setSource(const SoundSource &source)
{
    m_sound.setSource(source);
}
void UI_Sound::setVolume(float volume)
{
    m_sound.setVolume(volume);
}
void UI_Sound::setPlaybackSpeed(float speed)
{
    m_sound.setPlaybackSpeed(speed);
}
void UI_Sound::setLoops(int count)
{
    m_sound.setLoops(count);
}
void UI_Sound::toggleRepeat(bool toggleOn)
{
    DEBUGLN(toggleOn);
  #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    if(toggleOn)
        m_sound.setLoops(QMediaPlayer::Infinite);
    else
        m_sound.setLoops(1);
  #endif
}
bool UI_Sound::isRepeating() const
{
  #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    return m_sound.getLoops() == QMediaPlayer::Loops::Infinite;
  #else
  return false;
  #endif
}
void UI_Sound::setName(const std::string &name)
{
    m_sound.setName(name);
    ui->name_label->setText(m_sound.getName().c_str());
}
