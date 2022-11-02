#include "ui_soundSettings.h"
#include "ui_ui_soundSettings.h"

UI_SoundSettings::UI_SoundSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_SoundSettings)
{
    ui->setupUi(this);
    m_sound = nullptr;

    ui->play_pushButton->setIcon(QIcon(":/icons/play.png"));      ui->play_pushButton->setText("");
    ui->pause_pushButton->setIcon(QIcon(":/icons/pause.png"));    ui->pause_pushButton->setText("");
    ui->stop_pushButton->setIcon(QIcon(":/icons/stop.png"));      ui->stop_pushButton->setText("");
    ui->repeat_pushButton->setIcon(QIcon(":/icons/repeat.png"));  ui->repeat_pushButton->setText("");
    ui->settings_pushButton->setIcon(QIcon(":/icons/settings.png"));  ui->settings_pushButton->setText("");
    ui->delete_pushButton->setIcon(QIcon(":/icons/close.png"));   ui->delete_pushButton->setText("");

    connect(ui->play_pushButton,&QPushButton::clicked,this,&UI_SoundSettings::play);
    connect(ui->pause_pushButton,&QPushButton::clicked,this,&UI_SoundSettings::pause);
    connect(ui->stop_pushButton,&QPushButton::clicked,this,&UI_SoundSettings::stop);
    connect(ui->repeat_pushButton,&QPushButton::toggled,this,&UI_SoundSettings::toggleRepeat);
}

UI_SoundSettings::~UI_SoundSettings()
{
    delete ui;
    m_sound = nullptr;
}


void UI_SoundSettings::setSound(Sound *sound)
{
    if(m_sound)
        disconnect(m_sound, &QObject::destroyed, this, &UI_SoundSettings::onSoundDeleted);
    m_sound = sound;
    ui->name_label->setText(m_sound->getName().c_str());
    if(m_sound)
    {
        connect(m_sound, &QObject::destroyed, this, &UI_SoundSettings::onSoundDeleted);
        ui->repeat_pushButton->setDown(m_sound->getLoops() == Sound::Loops::Infinite);
    }
}
Sound *UI_SoundSettings::getSound() const
{
    return m_sound;
}

const SoundSource &UI_SoundSettings::getSource() const
{
    if(!m_sound)
    {
        const static SoundSource dummy;
        return dummy;
    }
    return m_sound->getSource();
}
float UI_SoundSettings::getVolume() const
{
    if(!m_sound)
        return 0;
    return m_sound->getVolume();
}
float UI_SoundSettings::getPlaybackSpeed() const
{
    if(!m_sound)
        return 0;
    return m_sound->getPlaybackSpeed();
}
unsigned int UI_SoundSettings::getLoops() const
{
    if(!m_sound)
        return 0;
    return m_sound->getLoops();
}
const std::string &UI_SoundSettings::getName() const
{
    if(!m_sound)
    {
        const static std::string dummy;
        return dummy;
    }
    return m_sound->getName();
}
void UI_SoundSettings::closeEvent(QCloseEvent *)
{
    m_sound->stop();
}

void UI_SoundSettings::play()
{
    if(m_sound)
        m_sound->play();
}
void UI_SoundSettings::pause()
{
    if(m_sound)
        m_sound->pause();
    emit onPlaybackPaused();
}
void UI_SoundSettings::stop()
{
    if(m_sound)
        m_sound->stop();
    emit onPlaybackStopped();
}

void UI_SoundSettings::setSource(const SoundSource &source)
{
    if(m_sound)
        m_sound->setSource(source);
}
void UI_SoundSettings::setVolume(float volume)
{
    if(m_sound)
        m_sound->setVolume(volume);
}
void UI_SoundSettings::setPlaybackSpeed(float speed)
{
    if(m_sound)
        m_sound->setPlaybackSpeed(speed);
}
void UI_SoundSettings::setLoops(int count)
{
    if(m_sound)
        m_sound->setLoops(count);
}
void UI_SoundSettings::toggleRepeat(bool toggleOn)
{
    if(!m_sound)
        return;
    if(toggleOn)
    {
        m_sound->setLoops(Sound::Loops::Infinite);
    }
    else
    {
        m_sound->setLoops(1);
    }
}
bool UI_SoundSettings::isRepeating() const
{
    if(!m_sound)
        return false;
    return m_sound->getLoops() == Sound::Loops::Infinite;
}
void UI_SoundSettings::setName(const std::string &name)
{
    if(!m_sound)
        return;
    m_sound->setName(name);
    ui->name_label->setText(m_sound->getName().c_str());
}

void UI_SoundSettings::onSoundDeleted()
{
    m_sound = nullptr;
}
