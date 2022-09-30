#include "sound.h"

Sound::Sound()
{
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_player.setAudioOutput(&m_output);
}
Sound::Sound(const SoundSource &source)
{
    connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_source = source;
    m_player.setAudioOutput(&m_output);
}
Sound::~Sound()
{

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
void Sound::save(QXmlStreamWriter *writer)
{
    if(!writer) return;
    writer->writeStartElement("Sound");
    writer->writeAttribute("name",m_name.c_str());
    writer->writeAttribute("loops",QString::number(getLoops()));
    writer->writeAttribute("volume",QString::number(getVolume()));
    writer->writeAttribute("speed",QString::number(getPlaybackSpeed()));
    m_source.save(writer);
    writer->writeEndElement();
}
void Sound::load(QXmlStreamReader *reader)
{
    if(!reader) return;
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
