#include "sound.h"
#include <QCoreApplication>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QAudioOutput *Sound::m_output = nullptr;
#endif

size_t Sound::m_stackSize = 10;
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
    //for(size_t i=0; i<m_player.size(); ++i)
    //    connect(m_player[i],&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    //setStackSize(1);
    setPlaymode(Playmode::Music);
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    //m_player.setAudioOutput(m_output);

    #else
    m_loops = 0;

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
    setPlaymode(Playmode::Music);
    //m_player.setAudioOutput(m_output);
    //connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
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
    //connect(&m_player,&QMediaPlayer::mediaStatusChanged,this,&Sound::onMediaStatusChanged);
    m_buttonPos.x = 0;
    m_buttonPos.y = 0;
    m_source = source;
    setPlaymode(Playmode::Music);
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)

    //m_player.setAudioOutput(m_output);
    #else
    m_loops = 0;

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
    return (float)m_player[0]->playbackRate();
}
int Sound::getLoops() const
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        return m_player[0]->loops();
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
    switch(m_playMode)
    {
        case Playmode::Music:
        {
            if(m_soundIsPlaying)
            {
                stop();
                return;
            }
            m_soundIsPlaying++;
            m_player[0]->play();
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            ++m_loopsCounter[0];
#endif
            break;
        }
        case Playmode::Stackable:
        {
            if(m_soundIsPlaying >= (signed)m_player.size())
                return; // All player slots currently used.
            size_t index = (m_soundIsPlaying++)%m_player.size();
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            ++m_loopsCounter[index];
#endif
            m_player[index]->play();
            break;
        }
    }
}
void Sound::pause()
{
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->pause();
    emit onPlaybackPaused();
}
void Sound::stop()
{
    m_soundIsPlaying = 0;
    for(size_t i=0; i<m_player.size(); ++i)
    {
        m_player[i]->stop();
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        m_loopsCounter[i] = 0;
#endif
    }
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
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->setSource(url);
#else
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->setMedia(QUrl::fromLocalFile(m_source.getAbsolutePath().c_str()));
#endif
}
void Sound::setVolume(float volume)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    m_volume = volume;
    qreal linearVolume = QAudio::convertVolume(volume, QAudio::LogarithmicVolumeScale,
                                                       QAudio::LinearVolumeScale);
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->setVolume(qRound(linearVolume*100));
#else
    m_output->setVolume(volume);
#endif
}
void Sound::setPlaybackSpeed(float speed)
{
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->setPlaybackRate((qreal)speed);
}
void Sound::setLoops(int count)
{
    #if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    for(size_t i=0; i<m_player.size(); ++i)
        m_player[i]->setLoops(count);
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

void Sound::setStackSize(size_t size)
{
    if(size == 0)
        size = 1;
    if(m_player.size() == size)
        return;


    if(m_player.size() > size)
    {
        std::vector<QMediaPlayer*> players = m_player;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        std::vector<int> loopsCount = m_loopsCounter;
        m_loopsCounter.clear();
#endif
        m_player.clear();
        while(players.size() > size)
        {
            delete players[players.size()-1];
            players[players.size()-1] = nullptr;
        }
        for(size_t i=0; i<players.size(); ++i)
            if(players[i])
            {
                m_player.push_back(players[i]);
                std::vector<QMediaPlayer*> players = m_player;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                m_loopsCounter.push_back(loopsCount[i]);
#endif
            }
        return;
    }
    while(m_player.size() < size)
    {
        QMediaPlayer *player = new QMediaPlayer;
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        player->setAudioOutput(m_output);
#endif
        connect(player, &QMediaPlayer::mediaStatusChanged, this, &Sound::onMediaStatusChanged);
        m_player.push_back(player);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        m_loopsCounter.push_back(0);
#endif
    }
}
Sound::Playmode Sound::getPlaymode() const
{
    return m_playMode;
}
void Sound::setPlaymode(Playmode mode)
{
    m_playMode = mode;
    switch(m_playMode)
    {
        case Playmode::Music:
        {
            setStackSize(1);
            break;
        }
        case Playmode::Stackable:
        {
            setStackSize(m_stackSize);
            break;
        }
    }
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
            m_soundIsPlaying--;
#ifdef DBG_SOUND
            DEBUGLN("Sound: \""<<m_source.getAbsolutePath().c_str()<<"\" finished playback");
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            size_t currentPlayerIndex = 0;
            QMediaPlayer *currentPlayer = dynamic_cast<QMediaPlayer*>(QObject::sender());
            if(currentPlayer)
            {
                for(size_t i=0; i<m_player.size(); ++i)
                    if(m_player[i] == currentPlayer)
                    {
                        currentPlayerIndex = i;
                        break;
                    }
            }
            if(m_loops == Loops::Infinite)
            {
                play();
                return;
            }
            if(currentPlayer)
            {
                if(m_loopsCounter[currentPlayerIndex] >= m_loops)
                {
                    m_loopsCounter[currentPlayerIndex] = 0;
                    emit onPlaybackFinished();
                }
                else
                {
                    play();
                }
            }
#else
            if(m_soundIsPlaying == 0)
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
