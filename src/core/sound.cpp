#include "sound.h"

QAudioOutput Sound::m_output;
Sound::Sound()
    : QObject()
    , ISerializable()
{
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_player.setAudioOutput(&m_output);
}
Sound::Sound(const Sound &other)
    : QObject()
    , ISerializable(other)
{
    this->operator=(other);
}
Sound::Sound(const SoundSource &source)
    : QObject()
    , ISerializable()
{
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_source = source;
    m_player.setAudioOutput(&m_output);
}
Sound::~Sound()
{

}
const Sound &Sound::operator=(const Sound &other)
{
    ISerializable::operator=(other);
    m_name = other.m_name;
    if(other.m_source.isValid())
        setSource(other.m_source);
    setPlaybackSpeed(other.getPlaybackSpeed());
    setLoops(other.getLoops());
    setVolume(other.getVolume());
    return *this;
}

const QAudioOutput &Sound::getAudioOutput()
{
    return m_output;
}
/*
void Sound::setID(const std::string &id)
{
    m_id = id;
}
const std::string &Sound::getID() const
{
    return m_id;
}*/

const SoundSource &Sound::getSource() const
{
    return m_source;
}
float Sound::getVolume() const
{
    return m_output.volume();
}
float Sound::getPlaybackSpeed() const
{
    return (float)m_player.playbackRate();
}
int Sound::getLoops() const
{
    return m_player.loops();
}
const std::string &Sound::getName() const
{
    return m_name;
}

std::string Sound::className() const
{
    return "Sound";
}
QJsonObject Sound::save() const
{
    return combine(ISerializable::save(),
    QJsonObject
    {
        {"name", m_name.c_str()},
        {"loops", getLoops()},
        {"volume", getVolume()},
        {"speed", getPlaybackSpeed()},
        {"source", m_source.getAbsolutePath().c_str()}
    });
}
bool Sound::read(const QJsonObject &reader)
{
    //QJsonObject data = reader.take("Sound").toObject();
    ISerializable::read(reader);

    bool success = true;
    int loops = 0;
    float volume = 0.5;
    float speed = 1;
    std::string source;
    success &= extract(reader,m_name,"name");
    success &= extract(reader,loops,"loops");
    success &= extract(reader,volume,"volume");
    success &= extract(reader,speed,"speed");
    success &= extract(reader,source,"source");


    if(!success)
    {
        WARNING("Kann Sound "<<m_name<<" nicht korrekt laden.");
        return false;
    }

    setLoops(loops);
    setVolume(volume);
    setPlaybackSpeed(speed);
    m_source.setAbsolutePath(source);
    setSource(m_source);

    return true;
}
void Sound::postLoad()
{

}

void Sound::play()
{
    if(!m_source.isValid())
    {
        WARNING(m_source.getAbsolutePath().c_str()<<" is not valid");
        return;
    }
#ifdef DBG_SOUND
    DEBUGLN("Starting sound: \""<<m_source.getAbsolutePath().c_str()<<"\"");
#endif
    m_player.play();
}
void Sound::pause()
{
    m_player.pause();
    emit onPlaybackPaused();
}
void Sound::stop()
{
    m_player.stop();
    emit onPlaybackStopped();
}

void Sound::setSource(const SoundSource &source)
{
    m_source = source;
    if(!m_source.isValid())
    {
        WARNING(m_source.getAbsolutePath().c_str()<<" is not valid\n");
        return;
    }
    m_player.setSource(QUrl::fromLocalFile(m_source.getAbsolutePath().c_str()));
}
void Sound::setVolume(float volume)
{
    m_output.setVolume(volume);
}
void Sound::setPlaybackSpeed(float speed)
{
    m_player.setPlaybackRate((qreal)speed);
}
void Sound::setLoops(int count)
{
    m_player.setLoops(count);
}
void Sound::setName(const std::string &name)
{
    m_name = name;
}

void Sound::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
        case QMediaPlayer::MediaStatus::NoMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::LoadingMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::LoadedMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::StalledMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::BufferingMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::BufferedMedia:
        {
            break;
        }
        case QMediaPlayer::MediaStatus::EndOfMedia:
        {
#ifdef DBG_SOUND
            DEBUGLN("Sound: \""<<m_source.getAbsolutePath().c_str()<<"\" finished playback");
#endif
            emit onPlaybackFinished();
            break;
        }
        case QMediaPlayer::MediaStatus::InvalidMedia:
        {
            break;
        }
    }
}
