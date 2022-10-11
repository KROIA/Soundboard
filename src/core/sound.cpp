#include "sound.h"

QAudioOutput Sound::m_output;
Sound::Sound()
    : QObject()
    , ISerializable()
{
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_player.setAudioOutput(&m_output);
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
/*
Sound *Sound::instantiate(const std::filesystem::path &path,
                          const std::string &id)
{
    return nullptr;
}
*/
const QAudioOutput &Sound::getAudioOutput()
{
    return m_output;
}

void Sound::setID(const std::string &id)
{
    m_id = id;
}
const std::string &Sound::getID() const
{
    return m_id;
}

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
ISerializable* Sound::clone(const QJsonObject &reader) const
{
    Sound *obj = new Sound();
    obj->read(reader);
    return obj;
}
QJsonObject Sound::save() const
{
    return QJsonObject
    {
        {"id", m_id.c_str()},
        {"name", m_name.c_str()},
        {"loops", getLoops()},
        {"volume", getVolume()},
        {"speed", getPlaybackSpeed()},
    };
}
bool Sound::read(const QJsonObject &reader)
{
    //QJsonObject data = reader.take("Sound").toObject();

    bool success = true;
    int loops = 0;
    float volume = 0.5;
    float speed = 1;
    success &= extract(reader,m_id,"id");
    success &= extract(reader,m_name,"name");
    success &= extract(reader,loops,"loops");
    success &= extract(reader,volume,"volume");
    success &= extract(reader,speed,"speed");

    if(!success)
        return false;

    setLoops(loops);
    setVolume(volume);
    setPlaybackSpeed(speed);

    return true;
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
        WARNING(m_source.getAbsolutePath().c_str()<<" is not valid");
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
