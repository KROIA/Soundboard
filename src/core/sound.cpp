#include "sound.h"
#include <QCoreApplication>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QAudioOutput *Sound::m_output = nullptr;
#endif

Sound::Sound()
    : QObject()
    , ISerializable()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
    m_output = new QAudioOutput;
#endif
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    m_player.setAudioOutput(m_output);
    #else
    m_loops = 0;
    m_loopsCounter = 0;
    #endif
    setVolume(1);
    m_soundIsPlaying = false;
}
Sound::Sound(const Sound &other)
    : QObject()
    , ISerializable(other)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
    m_output = new QAudioOutput;
#endif
    m_player.setAudioOutput(m_output);
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    this->operator=(other);
}
Sound::Sound(const SoundSource &source)
    : QObject()
    , ISerializable()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if(!m_output)
        m_output = new QAudioOutput;
#else
    m_output = new QAudioOutput;
#endif
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    m_source = source;
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    m_player.setAudioOutput(m_output);
    #else
    m_loops = 0;
    m_loopsCounter = 0;
    #endif
    m_soundIsPlaying = false;
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
    m_buttonPos = other.m_buttonPos;
    setPlaybackSpeed(other.getPlaybackSpeed());
    setLoops(other.getLoops());
    setVolume(other.getVolume());
    return *this;
}

/*const QAudioOutput &Sound::getAudioOutput()
{
    return *m_output;
}
*/
const SoundSource &Sound::getSource() const
{
    return m_source;
}
float Sound::getVolume() const
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return m_volume;
#else
    return m_output->volume();
#endif
}
float Sound::getPlaybackSpeed() const
{
    return (float)m_player.playbackRate();
}
int Sound::getLoops() const
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        return m_player.loops();
    #else
        return m_loops;
    #endif
}
const std::string &Sound::getName() const
{
    return m_name;
}
bool Sound::soundIsPlaying() const
{
    return m_soundIsPlaying;
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
        {"source", m_source.getAbsolutePath().c_str()},
        {"x",m_buttonPos.x},
        {"y",m_buttonPos.y}
    });
}
bool Sound::read(const QJsonObject &reader)
{
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
    success &= extract(reader,m_buttonPos.x,"x");
    success &= extract(reader,m_buttonPos.y,"y");


    if(!success)
    {
        WARNING("Kann Sound "<<m_name.c_str()<<" nicht korrekt laden.");
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
        WARNING("Path: \""<<m_source.getAbsolutePath().c_str()<<"\" is not valid");
        return;
    }
#ifdef DBG_SOUND
    DEBUGLN("Starting sound: \""<<m_source.getAbsolutePath().c_str()<<"\"");
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    ++m_loopsCounter;
#endif
    m_soundIsPlaying = true;
    m_player.play();
}
void Sound::pause()
{
    m_player.pause();
    emit onPlaybackPaused();
}
void Sound::stop()
{
    m_soundIsPlaying = false;
    m_player.stop();
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    m_loopsCounter = 0;
#endif
    emit onPlaybackStopped();
}

void Sound::setSource(const SoundSource &source)
{
    m_source = source;
    if(!m_source.isValid())
    {
        WARNING("Path: \""<<m_source.getAbsolutePath().c_str()<<"\" is not valid, trying relative path...\n");
        SoundSource testSrc(QCoreApplication::applicationDirPath().toStdString()+ "\\"+source.getAbsolutePath());
        if(!testSrc.isValid())
        {
            WARNING("Path: \""<<testSrc.getAbsolutePath().c_str()<<"\" is not valid\n");
            return;
        }
        m_source = testSrc;
    }
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    QUrl url = QUrl::fromLocalFile(m_source.getAbsolutePath().c_str());
    m_player.setSource(url);
#else
    m_player.setMedia(QUrl::fromLocalFile(m_source.getAbsolutePath().c_str()));
#endif
}
void Sound::setVolume(float volume)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    m_volume = volume;
    qreal linearVolume = QAudio::convertVolume(volume, QAudio::LogarithmicVolumeScale,
                                                       QAudio::LinearVolumeScale);
    m_player.setVolume(qRound(linearVolume*100));
#else
    m_output->setVolume(volume);
#endif
}
void Sound::setPlaybackSpeed(float speed)
{
    m_player.setPlaybackRate((qreal)speed);
}
void Sound::setLoops(int count)
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    m_player.setLoops(count);
    #else
    m_loops = count;
    #endif
}
void Sound::setName(const std::string &name)
{
    m_name = name;
    emit onNameChanged(m_name);
}
void Sound::setButtonCoord(int x, int y)
{
    m_buttonPos.x = x;
    m_buttonPos.y = y;
}

void Sound::setButtonCoord(const Coord &pos)
{
    m_buttonPos = pos;
}

const Coord &Sound::getButtonCoord() const
{
    return m_buttonPos;
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
            m_soundIsPlaying = false;
#ifdef DBG_SOUND
            DEBUGLN("Sound: \""<<m_source.getAbsolutePath().c_str()<<"\" finished playback");
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            if(m_loops == Loops::Infinite)
            {
                play();
                return;
            }
            if(m_loopsCounter >= m_loops)
            {
                m_loopsCounter = 0;
                emit onPlaybackFinished();
            }
            else
            {
                play();
            }
#else
            emit onPlaybackFinished();

#endif
            break;
        }
        case QMediaPlayer::MediaStatus::InvalidMedia:
        {
            break;
        }
    }
}
